#ifndef IUMDHCREATOR_H
#define IUMDHCREATOR_H

#include "iumdh.h"
#include "idatamodel/isettings.h"
#include "ilogic/icommandexecuter.h"
#include "customuniqueptr.h"

namespace gui
{
    struct IUmdhCreator
    {
        virtual ~IUmdhCreator() = default;

        virtual unique_ptr<IUmdh> create(ISettings*, ICommandExecuter*) const = 0;
    };
}

#endif // IUMDHCREATOR_H
