#include "application.h"
#include <QCoreApplication>
#include <QtQuick>

namespace Spark {

Application::Application(QObject *parent)
    :   QObject(parent), m_view(new QQuickView)
{

}


void Application::initialize()
{
    m_navigation.initialize();
    registerQmlTypes();
    setupQuickEnvironment();
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

    m_view->setSource(QUrl::fromLocalFile(applicationDir + "/interfaces/default/main.qml"));
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
}

void Application::showUserInterface()
{
    m_view->showFullScreen();
}

}
