#ifndef COMMANDEXECUTERPROVIDER_H
#define COMMANDEXECUTERPROVIDER_H

#include "umdh.logic.global.h"
#include "ilogic/icommandexecutercreator.h"

namespace logic
{
    UMDH_LOGIC_EXPORT gui::unique_ptr<gui::ICommandExecuterCreator> getCommandExecuterCreator();
}

#endif // COMMANDEXECUTERPROVIDER_H
