#include "interface/commandexecuterprovider.h"
#include "impl/ccommandexecutercreator.h"


gui::unique_ptr<gui::ICommandExecuterCreator> logic::getCommandExecuterCreator()
{
    return gui::make_unique<CCommandExecuterCreator>();
}
