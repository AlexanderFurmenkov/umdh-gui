#ifndef IREPORTMANAGER_H
#define IREPORTMANAGER_H

#include "ireportfilter.h"
#include "ireportsorter.h"
#include "idatamodel/ireport.h"

#pragma warning(push, 0)
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#pragma warning(pop)

namespace gui
{
    using ReportManagerObserver = std::function<void()>;
    using ProgressNotifier = std::function<void(int)>;
    using CallsByCountMap = std::multimap<std::ptrdiff_t, std::wstring>;

    struct StackFrameDisplayData
    {
        std::wstring title;
        std::wstring body;
    };
    using StackFrameDisplayDataList = std::list<StackFrameDisplayData>;

    struct IReportManager
    {
        virtual ~IReportManager() = default;

        virtual void setSourceReport(std::wstring pathToReport) = 0;
        virtual std::wstring getSourceReport() const = 0;

        virtual void setFilter(gui::unique_ptr<IReportFilter>) = 0;
        virtual void setSorter(gui::unique_ptr<IReportSorter>) = 0;

        virtual std::wstring getProcessedReport(ProgressNotifier) = 0;
        virtual StackFrameDisplayDataList getProcessedReportList(ProgressNotifier) = 0;

        virtual size_t getUniqueStacksCount() const = 0;
        virtual size_t getAllocationsCount() const = 0;
        virtual size_t getAllocatedBytes() const = 0;

        virtual CallsByCountMap calculateCallsCount(gui::ProgressNotifier progressNotifier) = 0;

        virtual void setUpdateNotifier(ReportManagerObserver) = 0;
    };
}

#endif // IREPORTMANAGER_H
