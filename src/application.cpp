#include "application.h"
#include "power/power.h"
#include <QCoreApplication>
#include <QtQuick>
#include <QFile>

namespace Spark {

Application::Application(QObject *parent)
    :   QObject(parent),
      m_launchController(new LaunchController(this)),
      m_view(new QQuickView),
      m_power(powerFactory(this))
{
    QGuiApplication::addLibraryPath(QCoreApplication::applicationDirPath() + QStringLiteral("/plugins"));

    connect(m_launchController.data(), &LaunchController::stateChanged, this, &Application::processStateChanged);
    connect(m_launchController.data(), &LaunchController::stateChanged, this, &Application::onStateChanged);

    connect(m_view->engine(), &QQmlEngine::quit, &QCoreApplication::quit);
}

bool Application::allowExit() const
{
    return m_config.allowExit();
}

bool Application::allowShutdown() const
{
    return m_config.allowShutdown();
}

bool Application::allowRestart() const
{
    return m_config.allowRestart();
}

void Application::initialize()
{
    parseConfiguration();
    m_navigation.initialize();
    registerQmlTypes();
    setupQuickEnvironment();
    m_launchController->initialize();
}

void Application::registerQmlTypes()
{
    Navigation::registerTypes();
    qmlRegisterUncreatableType<Application>("Spark", 0, 1, "Spark", "Can not instantiate Spark.");
}

void Application::setupQuickEnvironment()
{
    const QString applicationDir = QCoreApplication::applicationDirPath();

    m_view->engine()->addImportPath(applicationDir + QStringLiteral("/quick"));
    m_view->engine()->addPluginPath(applicationDir + QStringLiteral("/quick"));
    m_view->engine()->addPluginPath(applicationDir + QStringLiteral("/plugins"));
    m_view->engine()->addImportPath(applicationDir + QStringLiteral("/modules/"));
    m_view->engine()->rootContext()->setContextProperty("spark", QVariant::fromValue(this));
    m_view->engine()->rootContext()->setContextProperty("power", QVariant::fromValue(m_power.data()));

    m_view->setSource(QUrl::fromLocalFile(applicationDir + "/interfaces/default/main.qml"));
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->setCursor(QCursor(Qt::BlankCursor));
}

void Application::showUserInterface()
{
    m_view->showFullScreen();
}

QObject * Application::launchers() const
{
    return m_launchController->model();
}

Application::ProcessState Application::processState() const
{
    return static_cast<ProcessState>(m_launchController->state());
}

bool Application::launch(int index)
{
    return m_launchController->launch(index);
}

void Application::onStateChanged()
{
    if (processState() == Application::NotRunning)
    {
        m_view->raise();
        m_view->requestActivate();
    }
}

void Application::parseConfiguration()
{
    const QString applicationDir = QCoreApplication::applicationDirPath();
    const QString configFile = applicationDir + "/spark.xml";

    QFile file(configFile);
    if (file.open(QIODevice::ReadOnly))
    {
        m_config.parse(file.readAll());
        file.close();
    }
    else
    {
        qFatal("Failed to read configuration file. See the README for how to set up a valid configuration file.");
    }

    qDebug() << "Configuration options: " << endl
             << "Allow exit: " << m_config.allowExit() << endl
             << "Allow shutdown: " << m_config.allowShutdown() << endl
             << "Allow restart: " << m_config.allowRestart();
}

}
