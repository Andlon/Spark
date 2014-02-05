#include "launchcontroller.h"

#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QDebug>

namespace Spark {

namespace {

const QString TEMPLATE_FILENAME = QStringLiteral("template.xml");
const QString LAUNCHERS_FILENAME = QStringLiteral("spark.xml");
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
    :   QObject(parent),
      m_process(new QProcess),
      m_launchers(new LauncherCollectionModel)
{
    connect(m_process.data(), &QProcess::stateChanged, this, &LaunchController::stateChanged);
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
        QVector<Launcher> launchers = m_loader.loadLaunchers(data, applicationDir);

        // Assign unique IDs to the launchers
        for (int i = 0; i < launchers.count(); ++i)
            launchers[i].setId(i);

        m_launchers->setLaunchers(launchers);
    }
}

QProcess::ProcessState LaunchController::state() const
{
    return m_process->state();
}

QObject * LaunchController::model() const
{
    return m_launchers.data();
}

bool LaunchController::launch(int index)
{
    if (m_process->state() != QProcess::NotRunning)
        return false;

    const QVector<Launcher> launchers = m_launchers->launchers();
    if (index < 0 || index >= m_launchers->launchers().count())
        return false;

    const Launcher & launcher = launchers[index];
    m_process->start(launcher.execPath());

    if (m_process->state() == QProcess::NotRunning)
    {
        // If state is NotRunning immediately after launching, it means something failed
        return false;
    }

    return true;
}



}
