#pragma once

#include "powermanager.h"

#ifdef Q_OS_WIN

#include <windows.h>

class WindowsPowerManager : public PowerManager
{
    Q_OBJECT
public:
    explicit WindowsPowerManager(QObject *parent = 0);

    bool canReboot() const;
    bool canShutdown() const;

public slots:
    void shutdown();
    void reboot();

private:
    bool m_hasPowerControl;
};

BOOL SetPrivilege(
        HANDLE hToken,          // access token handle
        LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
        BOOL bEnablePrivilege   // to enable or disable privilege
        );

#endif
