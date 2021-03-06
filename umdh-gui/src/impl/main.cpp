#include "src/impl/mainwindow.h"

#include "serializerfactorycreatorprovider.h"
#include "objectfactorycreator.h"

#include "umdhcreatorprovider.h"
#include "reportmanagercreatorprovider.h"
#include "filterfactorycreatorprovider.h"
#include "sorterfactorycreatorprovider.h"
#include "commandexecuterprovider.h"

#pragma warning(push, 0)
#include <QApplication>
#pragma warning(pop)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("UMDH-GUI");
    QCoreApplication::setApplicationVersion("1.0.0");

    auto pObjectFactory = datamodel::getObjectFactory();
    auto pSerializerFactoryCreator = datamodelserializer::getSerializerFactoryCreator();

    auto pSerializerFactory = pSerializerFactoryCreator->create(pObjectFactory.get());

    auto reportManagerCreator = logic::getReportManagerCreator();
    auto filterFactoryCreator = logic::getFilterFactoryCreator();
    auto sorterFactoryCreator = logic::getSorterFactoryCreator();
    auto umdhCreator = logic::getUmdhCreator();
    auto commandExecuter = logic::getCommandExecuterCreator();

    MainWindow w({pObjectFactory.get(),
                 pSerializerFactory.get(),
                 reportManagerCreator.get(),
                 filterFactoryCreator.get(),
                 sorterFactoryCreator.get(),
                 umdhCreator.get(),
                 commandExecuter.get()});
    w.show();

    return a.exec();
}
