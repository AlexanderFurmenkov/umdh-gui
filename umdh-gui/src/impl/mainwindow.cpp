#include "mainwindow.h"

#include "umdhwidget.h"
#include "reportwidget.h"
#include "metamodel.h"

#pragma warning(push, 0)
#include "ui_mainwindow.h"
#include <cassert>
#pragma warning(pop)

using namespace gui;

MainWindow::MainWindow(const MainWindowArgs &mainWindowArgs,
                       QWidget *parent)
    :
      QMainWindow(parent),
      m_pUi(new Ui::MainWindow)
{
    assert(m_pUi);

    m_pUi->setupUi(this);
    init(mainWindowArgs);
}

MainWindow::~MainWindow()
{
    delete m_pUi;
}

void MainWindow::init(const MainWindowArgs& mainWindowArgs)
{
    assert(mainWindowArgs.pObjectFactory);
    assert(mainWindowArgs.pSerializerFactory);
    assert(mainWindowArgs.pReportManagerCreator);
    assert(mainWindowArgs.pFilterFactoryCreator);
    assert(mainWindowArgs.pSorterFactoryCreator);
    assert(mainWindowArgs.pUmdhCreator);
    assert(mainWindowArgs.pCommandExecuterCreator);

    createTabUmdh(mainWindowArgs);
    createTabReport(mainWindowArgs);
}

void MainWindow::createTabUmdh(const MainWindowArgs& mainWindowArgs)
{
    m_pSettings = gui::dynamic_unique_cast<gui::ISettings>(mainWindowArgs.pObjectFactory->get(cSettingsType));
    pCommandExecuter = mainWindowArgs.pCommandExecuterCreator->create();
    m_pUmdh = mainWindowArgs.pUmdhCreator->create(m_pSettings.get(), pCommandExecuter.get());
    m_pUi->tabWidget->addTab(new UmdhWidget(m_pSettings.get(), m_pUmdh.get(), pCommandExecuter.get()), "UMDH");
}

void MainWindow::createTabReport(const MainWindowArgs& mainWindowArgs)
{
    m_pFilterFactory = mainWindowArgs.pFilterFactoryCreator->create();
    m_pSorterFactory = mainWindowArgs.pSorterFactoryCreator->create();
    m_pUi->tabWidget->addTab(new ReportWidget(mainWindowArgs.pObjectFactory,
                                              mainWindowArgs.pSerializerFactory,
                                              mainWindowArgs.pReportManagerCreator,
                                              m_pFilterFactory.get(),
                                              m_pSorterFactory.get()),
                                              tr("Report"));
}
