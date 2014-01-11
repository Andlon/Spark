#include "application.h"
#include <QCoreApplication>
#include <QtQuick>

namespace Spark {

Application::Application(QObject *parent)
    :   QObject(parent),
      m_launchController(new LaunchController(this)),
      m_view(new QQuickView)
{
    connect(m_launchController.data(), &LaunchController::stateChanged, this, &Application::processStateChanged);
}


void Application::initialize()
{
    m_navigation.initialize();
    registerQmlTypes();
    setupQuickEnvironment();
    m_launchController->initialize();
}

void Application::registerQmlTypes()
{
    Navigation::registerTypes();
}

void Application::setupQuickEnvironment()
{
    const QString applicationDir = QCoreApplication::applicationDirPath();

    m_view->engine()->addImportPath(applicationDir + QStringLiteral("/quick"));
    m_view->engine()->addPluginPath(applicationDir + QStringLiteral("/quick"));
    m_view->engine()->addPluginPath(applicationDir + QStringLiteral("/plugins"));
    m_view->engine()->addImportPath(applicationDir + QStringLiteral("/modules/"));
    m_view->engine()->rootContext()->setContextProperty("spark", QVariant::fromValue(this));

    m_view->setSource(QUrl::fromLocalFile(applicationDir + "/interfaces/default/main.qml"));
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
}

void Application::showUserInterface()
{
    m_view->showFullScreen();
}

QObject * Application::launchers() const
{
    return m_launchController->model();
}

QProcess::ProcessState Application::processState() const
{
    return m_launchController->state();
}

bool Application::launch(int index)
{
    return m_launchController->launch(index);
}

}
