#include "launcher.h"
#include <QXmlStreamReader>
#include <QDebug>

namespace Spark {

namespace {

void printWarningIfError(QXmlStreamReader &reader)
{
    if (reader.error() != QXmlStreamReader::NoError)
    {
        qWarning() << "Error during template XML parsing: " << reader.errorString();
    }
}

}

void LauncherLoader::loadTemplate(const QByteArray &xml)
{
    QXmlStreamReader reader(xml);

    while (reader.readNextStartElement())
    {
        if (reader.name() == "template")
            readTemplateElement(reader);
        else
        {
            qWarning() << "Skipping unknown XML element " << reader.name();
            reader.skipCurrentElement();
        }
    }

    printWarningIfError(reader);
}

QVector<Launcher> LauncherLoader::loadLaunchers(const QByteArray &xml) const
{
    QXmlStreamReader reader(xml);
    QVector<Launcher> launchers;

    while (reader.readNextStartElement())
    {
        if (reader.name() == "launchers")
            launchers += readLaunchers(reader);
        else
        {
            qWarning() << "Skipping unknown XML element " << reader.name();
            reader.skipCurrentElement();
        }
    }

    printWarningIfError(reader);
    return launchers;
}

void LauncherLoader::readTemplateElement(QXmlStreamReader &reader)
{
    const QString templateName = reader.attributes().value("name").toString();
    Launcher launcher;

    if (!templateName.isEmpty())
    {
        readLauncherParameters(reader, launcher);
        m_templates[templateName] = launcher;
    }
    else
    {
        qWarning() << "Template with missing name discovered while parsing XML.";
    }
}

void LauncherLoader::readLauncherParameters(QXmlStreamReader &reader, Launcher & launcher) const
{
    QStringList screenshots;

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

}
