#pragma once

#include <QString>
#include <QStringList>
#include <QHash>
#include <QVector>
#include <QDir>

class QXmlStreamReader;
class QDataStream;
class QDebug;

namespace Spark {

class Launcher {
public:
    explicit Launcher() : m_id(-1) { }

    int         id() const { return m_id; }
    QString     title() const { return m_title; }
    QString     description() const { return m_description; }
    QString     logoPath() const { return m_logoPath; }
    QString     execPath() const { return m_execPath; }
    QString     usage() const { return m_usage; }
    QStringList screenshotPaths() const { return m_screenshotPaths; }

    void setId(int id) { m_id = id; }
    void setTitle(const QString & title) { m_title = title; }
    void setDescription(const QString & description) { m_description = description; }
    void setLogoPath(const QString & logoPath) { m_logoPath = logoPath; }
    void setExecPath(const QString & execPath) { m_execPath = execPath; }
    void setUsage(const QString & usage) { m_usage = usage; }
    void setScreenshotPaths(const QStringList & paths) { m_screenshotPaths = paths; }

private:
    int         m_id;
    QString     m_title;
    QString     m_description;
    QString     m_logoPath;
    QString     m_execPath;
    QString     m_usage;
    QStringList m_screenshotPaths;
};

QDataStream & operator << (QDataStream & stream, const Launcher & launcher);
QDebug operator << (QDebug d, const Launcher & launcher);

class LauncherLoader {
public:
    void loadTemplate(const QByteArray & xml, const QString & relativeTo);
    QVector<Launcher> loadLaunchers(const QByteArray & xml, const QString & relativeToPath) const;

private:
    void                readTemplateElement(QXmlStreamReader & reader, const QDir & relativeToPath);
    void                readLauncherParameters(QXmlStreamReader &reader, Launcher & launcher) const;
    QVector<Launcher>   readLaunchers(QXmlStreamReader & reader) const;
    Launcher            readLauncher(QXmlStreamReader & reader) const;

    QHash<QString, Launcher>    m_templates;
};

}
