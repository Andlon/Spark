#include "launcher.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QTextStream>

namespace Spark {

namespace {

void printWarningIfError(QXmlStreamReader &reader)
{
    if (reader.error() != QXmlStreamReader::NoError)
    {
        qWarning() << "Error during template XML parsing: " << reader.errorString();
    }
}

QString makeAbsolutePath(const QString & path, const QDir & relativeTo)
{
    if (QDir::isAbsolutePath(path))
        return QDir::cleanPath(path);
    else
        return relativeTo.absoluteFilePath(path);
}

void makePathsAbsolute(Launcher & launcher, const QDir & relativeTo)
{
    launcher.setLogoPath(makeAbsolutePath(launcher.logoPath(), relativeTo));

    QStringList screenshots;
    for (const QString & path : launcher.screenshotPaths())
        screenshots << makeAbsolutePath(path, relativeTo);
    launcher.setScreenshotPaths(screenshots);
}

}

void LauncherLoader::loadTemplate(const QByteArray &xml, const QString &relativeToPath)
{
    QXmlStreamReader reader(xml);
    QDir relativeTo(relativeToPath);

    if (reader.readNextStartElement())
    {
        if (reader.name() == "template")
            readTemplateElement(reader, relativeTo);
        else
        {
            qWarning() << "Skipping unknown XML element " << reader.name();
            reader.skipCurrentElement();
        }
    }
    else
    {
        printWarningIfError(reader);
    }
}

QVector<Launcher> LauncherLoader::loadLaunchers(const QByteArray &xml, const QString &relativeToPath) const
{
    QXmlStreamReader reader(xml);
    QVector<Launcher> launchers;

    if (reader.readNextStartElement())
    {
        if (reader.name() == "launchers")
            launchers += readLaunchers(reader);
        else
        {
            qWarning() << "Skipping unknown XML element " << reader.name();
            reader.skipCurrentElement();
        }
    }
    else
    {
        printWarningIfError(reader);
    }

    QDir relativeTo(relativeToPath);
    for (Launcher & launcher : launchers)
        makePathsAbsolute(launcher, relativeTo);

    return launchers;
}

void LauncherLoader::readTemplateElement(QXmlStreamReader &reader, const QDir &relativeTo)
{
    const QString templateName = reader.attributes().value("name").toString();
    Launcher launcher;

    if (!templateName.isEmpty())
    {
        readLauncherParameters(reader, launcher);
        makePathsAbsolute(launcher, relativeTo);
        m_templates[templateName] = launcher;
    }
    else
    {
        qWarning() << "Template with missing name discovered while parsing XML.";
    }
}

void LauncherLoader::readLauncherParameters(QXmlStreamReader &reader, Launcher & launcher) const
{
    QStringList screenshots = launcher.screenshotPaths();

    while (reader.readNextStartElement())
    {
        const QStringRef element = reader.name();
        const QString text = reader.readElementText();

        if (element == "title")
            launcher.setTitle(text);
        else if (element == "description")
            launcher.setDescription(text);
        else if (element == "logo")
            launcher.setLogoPath(text);
        else if (element == "exec")
            launcher.setExecPath(text);
        else if (element == "usage")
            launcher.setUsage(text);
        else if (element == "screenshot")
            screenshots.append(text);
        else
            qWarning() << "Unknown element " << element << " found when parsing launcher/template XML.";

        printWarningIfError(reader);
    }

    launcher.setScreenshotPaths(screenshots);
    printWarningIfError(reader);
}

QVector<Launcher> LauncherLoader::readLaunchers(QXmlStreamReader &reader) const
{
    QVector<Launcher> launchers;

    while (reader.readNextStartElement())
    {
        if (reader.name() == "launcher")
            launchers += readLauncher(reader);
        else
        {
            reader.skipCurrentElement();
            qWarning() << "Unknown element " << reader.name() << " found when parsing launcher/template XML.";
        }
    }

    printWarningIfError(reader);
    return launchers;
}

Launcher LauncherLoader::readLauncher(QXmlStreamReader &reader) const
{
    const QString templateName = reader.attributes().value("template").toString();

    Launcher launcher = m_templates.value(templateName, Launcher());
    readLauncherParameters(reader, launcher);
    return launcher;
}

QDataStream & operator <<(QDataStream &stream, const Launcher &launcher)
{
    stream << "Title: " << launcher.title();
    stream << "Description: " << launcher.description();
    stream << "Logo: " << launcher.logoPath();
    stream << "Exec: " << launcher.execPath();
    stream << "Screenshots: " << launcher.screenshotPaths();

    return stream;
}

QDebug operator <<(QDebug d, const Launcher &launcher)
{
    d << "Title: " << launcher.title();
    d << "Description: " << launcher.description();
    d << "Logo: " << launcher.logoPath();
    d << "Exec: " << launcher.execPath();
    d << "Screenshots: " << launcher.screenshotPaths();

    return d;
}

}
