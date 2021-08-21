#ifndef CCOMMANDEXECUTERCREATOR_H
#define CCOMMANDEXECUTERCREATOR_H

#include "ilogic/icommandexecutercreator.h"

namespace logic
{
    class CCommandExecuterCreator : public gui::ICommandExecuterCreator
    {
    public:
        virtual ~CCommandExecuterCreator() = default;

        gui::unique_ptr<gui::ICommandExecuter> create() const override;
    };
}
#endif // CCOMMANDEXECUTERCREATOR_H
