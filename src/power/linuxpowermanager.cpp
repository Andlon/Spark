#include "linuxpowermanager.h"

#if (defined(Q_OS_LINUX) || defined(Q_OS_UNIX))

LinuxPowerManager::LinuxPowerManager(QObject *parent) : PowerManager(parent)
{
    m_service = "org.freedesktop.ConsoleKit";
    m_path = "/org/freedesktop/ConsoleKit/Manager";
    m_interface = "org.freedesktop.ConsoleKit.Manager";
}

QDBusMessage LinuxPowerManager::callMethod(const QString &method) const
{
    QDBusMessage m = QDBusMessage::createMethodCall(m_service, m_path, m_interface, method);
    return QDBusConnection::systemBus().call(m);
}

bool LinuxPowerManager::canShutdown() const
{
    //info(0, "Attempting to query for CanStop. ", Log::All);
    QDBusMessage m = callMethod("CanStop");
    if (m.type() == QDBusMessage::ReplyMessage)
    {
        if (m.arguments().count() > 0)
        {
            bool stop = m.arguments()[0].toBool();
      //      info(0, "Result of CanStop query: " + QString(stop ? "true" : "false") , Log::Verbose);
            return stop;
        }
    }
    else if (m.type() == QDBusMessage::ErrorMessage)
    {
    //    error(0, "DBus error: " + m.errorName() + ": " + m.errorMessage(), Log::Vital);
    }
    return false;
}

bool LinuxPowerManager::canReboot() const
{
    //info(0, "Attempting to query for CanReboot. ", Log::All);
    QDBusMessage m = callMethod("CanRestart");
    if (m.type() == QDBusMessage::ReplyMessage)
    {
        if (m.arguments().count() > 0)
        {
            bool reboot = m.arguments()[0].toBool();
      //      info(0, "Result of CanReboot query: " + QString(reboot ? "true" : "false") , Log::Verbose);
            return reboot;
        }
    }
    else if (m.type() == QDBusMessage::ErrorMessage)
    {
        //error(0, "DBus error: " + m.errorName() + ": " + m.errorMessage(), Log::Vital);
    }
    return false;
}

void LinuxPowerManager::shutdown()
{
    //info(0, "Attempting to shutdown system... ", Log::Standard);
    callMethod("Stop");
}

void LinuxPowerManager::reboot()
{
    //info(0, "Attempting to reboot system... ", Log::Standard);
    callMethod("Restart");
}

#endif
