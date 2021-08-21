#ifndef ICOMMANDEXECUTERCREATOR_H
#define ICOMMANDEXECUTERCREATOR_H

#include "icommandexecuter.h"
#include "customuniqueptr.h"

namespace gui
{
    struct ICommandExecuterCreator
    {
        virtual ~ICommandExecuterCreator() = default;

        virtual unique_ptr<ICommandExecuter> create() const = 0;
    };
}

#endif // ICOMMANDEXECUTERCREATOR_H
