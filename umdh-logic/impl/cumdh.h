#ifndef CUMDH_H
#define CUMDH_H

#include "ilogic/iumdh.h"
#include "idatamodel/isettings.h"
#include "ilogic/icommandexecuter.h"

namespace logic
{
    class CUmdh : public gui::IUmdh
    {
    public:
        CUmdh(gui::ISettings*, gui::ICommandExecuter*);

        void createSnapshot(std::wstring pathToSnapshot) override;
        void createReport(std::wstring reportPath, std::wstring pathToSnapshotOld, std::wstring pathToSnapshotNew) override;

    private:
        gui::ISettings *m_pSettings;
        gui::ICommandExecuter *m_pCommandExecuter;
    };
}

#endif // CUMDH_H
