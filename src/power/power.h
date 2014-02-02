#ifndef POWER_H
#define POWER_H

#include "powermanager.h"

#ifdef Q_OS_LINUX
#include "linuxpowermanager.h"
#endif

#ifdef Q_OS_WIN
#include "windowspowermanager.h"
#endif

inline PowerManager* powerFactory(QObject *parent = 0)
{
#if defined(Q_OS_LINUX)
    return new LinuxPowerManager(parent);
#elif defined(Q_OS_WIN)
    return new WindowsPowerManager(parent);
#else
    return new PowerManager(parent);
#endif
}

#endif // POWER_H
