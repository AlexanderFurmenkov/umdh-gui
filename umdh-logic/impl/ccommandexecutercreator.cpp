#include "ccommandexecutercreator.h"
#include "ccommandexecuter.h"

using namespace logic;

gui::unique_ptr<gui::ICommandExecuter> logic::CCommandExecuterCreator::create() const
{
    return gui::make_unique<CCommandExecuter>();
}
