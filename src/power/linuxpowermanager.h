#pragma once

#ifdef Q_OS_LINUX

#include <QString>
#include <QtDBus>

#include "powermanager.h"

class LinuxPowerManager : public PowerManager
{
    Q_OBJECT

public:
    explicit LinuxPowerManager(QObject *parent = 0);

    bool canReboot() const;
    bool canShutdown() const;

public slots:
    void shutdown();
    void reboot();

private:
    QDBusMessage callMethod(const QString &method) const;

    QString m_service;
    QString m_interface;
    QString m_path;
};

#endif
