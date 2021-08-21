#include "creportmanager.h"
#include "idatamodel/iclonable.h"
#include "metamodel.h"

#pragma warning(push, 0)
#include <cassert>
#include <fstream>
#include <codecvt>
#include <locale>

#include "windows.h"
#include "winnls.h"
#pragma warning(pop)

using namespace logic;

namespace
{
	std::string utf8_encode(const std::wstring& wstr)
	{
		if (wstr.empty()) return std::string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}

	std::wstring getFileContent(std::wstring filename)
	{
		std::wifstream file(utf8_encode(filename));
		std::wstring fileData((std::istreambuf_iterator<wchar_t>(file)),
			std::istreambuf_iterator<wchar_t>());
		return fileData;
	}
}

CReportManager::CReportManager(const gui::IObjectFactory *pObjectFactory,
	const gui::ISerializerFactory *pSerializerFactory,
	gui::unique_ptr<IHotPathCalculator> pHotPathCalculator)
	:
	m_pObjectFactory(pObjectFactory),
	m_pSerializerFactory(pSerializerFactory),
	m_pHotPathCalculator(std::move(pHotPathCalculator))
{
	assert(m_pObjectFactory);
	assert(m_pSerializerFactory);
	assert(m_pHotPathCalculator);
}

void CReportManager::setSourceReport(std::wstring pathToReport)
{
	if (m_pathToReport == pathToReport)
		return;

	m_pathToReport = std::move(pathToReport);
	m_pathToReportChanged = true;
	if (m_observer)
		m_observer();
}

std::wstring CReportManager::getSourceReport() const
{
	return m_pathToReport;
}

void CReportManager::setFilter(gui::unique_ptr<gui::IReportFilter> filter)
{
	m_reportFilterChanged = true;
	m_pFilter = std::move(filter);
	if (m_observer)
		m_observer();
}

void CReportManager::setSorter(gui::unique_ptr<gui::IReportSorter> sorter)
{
	m_reportSorterChanged = true;
	m_pSorter = std::move(sorter);
	if (m_observer)
		m_observer();
}

std::wstring CReportManager::getProcessedReport(gui::ProgressNotifier progressNotifier)
{
	processReport(progressNotifier);
	auto pReportSerializer = m_pSerializerFactory->get(dynamic_cast<gui::IDataObject *>(m_pReport.get()));
	auto result = pReportSerializer->toString();
	progressNotifier(100);
	return result;
}

gui::StackFrameDisplayDataList CReportManager::getProcessedReportList(gui::ProgressNotifier progressNotifier)
{
	processReport(progressNotifier);

	auto logEntries = m_pReport->getLogEntries();
	progressNotifier(95);
	gui::StackFrameDisplayDataList result;
	for (const auto &pLogEntry : logEntries)
	{
		auto pLogEntrySerializer = m_pSerializerFactory->get(dynamic_cast<gui::IDataObject *>(pLogEntry.get()));
		const std::ptrdiff_t allocatedBytes = pLogEntry->getNewBytes() - pLogEntry->getOldBytes();
		const std::ptrdiff_t allocationsCount = pLogEntry->getNewCount() - pLogEntry->getOldCount();
		std::wstring title = L"Allocated bytes: " + std::to_wstring(allocatedBytes) + L"; Allocation count: " + std::to_wstring(allocationsCount);
		result.push_back({ title, pLogEntrySerializer->toString() });
	}
	progressNotifier(100);
	return result;
}

void CReportManager::processReport(gui::ProgressNotifier progressNotifier)
{
	progressNotifier(1);
	const bool needPostProcessing = m_pathToReportChanged || m_reportFilterChanged || m_reportSorterChanged;
	reloadReportIfNeeded();
	resetReportChangeTriggers();
	progressNotifier(25);
	processReportBase(progressNotifier, needPostProcessing);
}

void CReportManager::resetReportChangeTriggers()
{
	m_pathToReportChanged = false;
	m_reportFilterChanged = false;
	m_reportSorterChanged = false;
}

void CReportManager::processReportBase(gui::ProgressNotifier progressNotifier, bool needPostProcessing)
{
	applyFilter();
	progressNotifier(50);
	applySorter();
	progressNotifier(75);

	if (needPostProcessing)
		postProcessing();

	progressNotifier(90);
}
void CReportManager::setUpdateNotifier(gui::ReportManagerObserver observer)
{
	m_observer = std::move(observer);
}

size_t CReportManager::getUniqueStacksCount() const
{
	return m_uniqueStackTraceCount;
}

size_t CReportManager::getAllocationsCount() const
{
	return m_allocationsCount;
}

size_t CReportManager::getAllocatedBytes() const
{
	return m_allocatedBytes;
}

gui::CallsByCountMap CReportManager::calculateCallsCount(gui::ProgressNotifier progressNotifier)
{
	if (!m_pReport)
		return {};

	processReport(progressNotifier);
	auto result = m_pHotPathCalculator->calculateCallsCount(m_pReport.get());
	progressNotifier(100);
	return result;
}

void CReportManager::reloadReportIfNeeded()
{
	if (m_pathToReport.empty())
		return;

	if (m_pathToReportChanged)
	{
		m_pSourceReport = readReportFromFile();
	}

	if (m_pathToReportChanged || m_reportFilterChanged || m_reportSorterChanged)
	{
		m_pReport = gui::dynamic_unique_cast<gui::IReport>(dynamic_cast<gui::IClonable *>(m_pSourceReport.get())->clone());
	}
}

gui::unique_ptr<gui::IReport> CReportManager::readReportFromFile() const
{
	auto pReport = m_pObjectFactory->get(cReportType);
	auto pReportSerializer = m_pSerializerFactory->get(pReport.get());
	gui::readSerializedString(m_pSerializerFactory, pReport.get(), getFileContent(m_pathToReport));
	return gui::dynamic_unique_cast<gui::IReport>(std::move(pReport));
}

void CReportManager::applyFilter()
{
	if (!m_pFilter)
		return;

	m_pReport = m_pFilter->get(std::move(m_pReport));
}

void CReportManager::applySorter()
{
	if (!m_pSorter)
		return;

	m_pReport = m_pSorter->sort(std::move(m_pReport));
}

void CReportManager::postProcessing()
{
	auto modules = m_pReport->getLoadedModules();
	modules.clear();
	m_pReport->setLoadedModules(std::move(modules));

	auto logEntries = m_pReport->getLogEntries();
	m_pReport->setTotalIncrease(nullptr);

	m_allocationsCount = 0;
	m_allocatedBytes = 0;
	m_uniqueStackTraceCount = logEntries.size();

	for (size_t i = 0; i < logEntries.size(); ++i)
	{
		const auto &pLogEntry = logEntries[i];
		const std::ptrdiff_t bytesDiff = static_cast<std::ptrdiff_t>(pLogEntry->getNewBytes()) - static_cast<std::ptrdiff_t>(pLogEntry->getOldBytes());
		if (bytesDiff > 0)
			m_allocatedBytes += bytesDiff;

		const std::ptrdiff_t allocationsCountDiff = static_cast<std::ptrdiff_t>(pLogEntry->getNewCount()) - static_cast<std::ptrdiff_t>(pLogEntry->getOldCount());
		if (allocationsCountDiff > 0)
			m_allocationsCount += pLogEntry->getNewCount() - pLogEntry->getOldCount();
	}
}
