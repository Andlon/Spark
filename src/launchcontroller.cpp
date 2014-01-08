#include "launchcontroller.h"

#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QDebug>

namespace Spark {

namespace {

const QString TEMPLATE_FILENAME = QStringLiteral("template.xml");
const QString LAUNCHERS_FILENAME = QStringLiteral("launchers.xml");
const QString TEMPLATE_DIRECTORY = QStringLiteral("/templates");

QStringList findTemplateDirectories(const QString & rootSearchDirectory)
{
    QDir dir(rootSearchDirectory);
    QStringList descriptors;

    for (const QString path : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir templateDir(dir.absoluteFilePath(path));
        if (templateDir.exists(TEMPLATE_FILENAME))
            descriptors << templateDir.absolutePath();
    }

    return descriptors;
}

}

LaunchController::LaunchController(QObject *parent)
    :   QObject(parent), m_launchers(new LauncherCollectionModel)
{

}

void LaunchController::initialize()
{
    const QString applicationDir = QCoreApplication::applicationDirPath();
    const QString templateDir = applicationDir + TEMPLATE_DIRECTORY;

    QStringList templateDirectories = findTemplateDirectories(templateDir);

    // Load templates
    for (const QString & directory : templateDirectories)
    {
        QFile templateXml(directory + "/" + TEMPLATE_FILENAME);
        if (templateXml.open(QIODevice::ReadOnly))
        {
            const QByteArray data = templateXml.readAll();
            m_loader.loadTemplate(data, directory);
        }
    }

    // Load launchers
    QFile launchersXml(applicationDir + "/" + LAUNCHERS_FILENAME);
    if (launchersXml.open(QIODevice::ReadOnly))
    {
        const QByteArray data = launchersXml.readAll();
        m_launchers->setLaunchers(m_loader.loadLaunchers(data, applicationDir));
    }
}

QObject * LaunchController::model() const
{
    return m_launchers.data();
}



}
