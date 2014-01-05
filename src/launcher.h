#pragma once

#include <QString>
#include <QStringList>
#include <QHash>
#include <QVector>

class QXmlStreamReader;
class QDataStream;

namespace Spark {

class Launcher {
public:
    QString     title() const { return m_title; }
    QString     description() const { return m_description; }
    QString     logoPath() const { return m_logoPath; }
    QString     execPath() const { return m_execPath; }
    QStringList screenshotPaths() const { return m_screenshotPaths; }

    void setTitle(const QString & title) { m_title = title; }
    void setDescription(const QString & description) { m_description = description; }
    void setLogoPath(const QString & logoPath) { m_logoPath = logoPath; }
    void setExecPath(const QString & execPath) { m_execPath = execPath; }
    void setScreenshotPaths(const QStringList & paths) { m_screenshotPaths = paths; }

private:
    QString     m_title;
    QString     m_description;
    QString     m_logoPath;
    QString     m_execPath;
    QStringList m_screenshotPaths;
};

QDataStream & operator << (QDataStream & stream, const Launcher & launcher);

class LauncherLoader {
public:
    void loadTemplate(const QByteArray & xml);
    QVector<Launcher> loadLaunchers(const QByteArray & xml) const;

private:
    void                readTemplateElement(QXmlStreamReader & reader);
    void                readLauncherParameters(QXmlStreamReader &reader, Launcher & launcher) const;
    QVector<Launcher>   readLaunchers(QXmlStreamReader & reader) const;
    Launcher            readLauncher(QXmlStreamReader & reader) const;

    QHash<QString, Launcher>  m_templates;
};

}
