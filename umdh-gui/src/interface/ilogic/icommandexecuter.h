#ifndef ICOMMANDEXECUTER_H
#define ICOMMANDEXECUTER_H

#pragma warning(push, 0)
#include <string>
#pragma warning(pop)

namespace gui
{
    struct ICommandExecuter
    {
        virtual ~ICommandExecuter() = default;

        virtual void execute(std::wstring pathToApp, std::wstring args) = 0;
    };
}

#endif // ICOMMANDEXECUTER_H
