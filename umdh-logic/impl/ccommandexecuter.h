#ifndef CCOMMANDEXECUTER_H
#define CCOMMANDEXECUTER_H

#include "ilogic/icommandexecuter.h"

namespace logic
{
    class CCommandExecuter : public gui::ICommandExecuter
    {
    public:
        void execute(std::wstring pathToApp, std::wstring args) override;
    };
}

#endif // CCOMMANDEXECUTER_H
