#include "cumdh.h"

#pragma warning(push, 0)
#include <cassert>
#pragma warning(pop)


using namespace logic;

namespace
{
    std::wstring wrap(std::wstring src)
    {
        return L"\"" + src + L"\"";
    }
}

CUmdh::CUmdh(gui::ISettings *pSettings, gui::ICommandExecuter* pCommandExecuter) : m_pSettings(pSettings), m_pCommandExecuter(pCommandExecuter)
{
    assert(m_pSettings);
    assert(m_pCommandExecuter);
}

void CUmdh::createSnapshot(std::wstring pathToSnapshot)
{
    if (pathToSnapshot.empty())
    {
        return;
    }

    std::wstring command;

    if (m_pSettings->getPID().empty())
        command = L"-pn:\"" + m_pSettings->getTargetProgramm() + L"\" -f:" + wrap(pathToSnapshot);
    else
        command = L"-p:" + m_pSettings->getPID() + L" -f:" +  wrap(pathToSnapshot);

    m_pCommandExecuter->execute(m_pSettings->getUmdhPath(), command);
}

void CUmdh::createReport(std::wstring reportPath, std::wstring pathToSnapshotOld, std::wstring pathToSnapshotNew)
{
    if (reportPath.empty() || pathToSnapshotOld.empty() || pathToSnapshotNew.empty())
    {
        return;
    }

    m_pCommandExecuter->execute(m_pSettings->getUmdhPath(),
                       wrap(pathToSnapshotOld) + L" " +
                       wrap(pathToSnapshotNew) + L" -f:" +
                       reportPath);
}
