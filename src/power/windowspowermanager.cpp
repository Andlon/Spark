#include "windowspowermanager.h"

#ifdef Q_OS_WIN

#define SHTDN_REASON_MAJOR_OTHER 0x00000000
#define SHTDN_REASON_MINOR_OTHER 0x00000000
#define SHTDN_REASON_FLAG_PLANNED 0x80000000

WindowsPowerManager::WindowsPowerManager(QObject *parent) :
    PowerManager(parent)
{
    HANDLE hToken;

     // Retrieve the current process token
     OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

     // Adjust the privileges to allow power control
     m_hasPowerControl = SetPrivilege(hToken, SE_SHUTDOWN_NAME, TRUE);

     // Clean up token
     CloseHandle(hToken);
}

bool WindowsPowerManager::canShutdown() const
{
    return m_hasPowerControl;
}

bool WindowsPowerManager::canReboot() const
{
    return m_hasPowerControl;
}

void WindowsPowerManager::reboot()
{
    if (canReboot())
        ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED);
}

void WindowsPowerManager::shutdown()
{
    if (canShutdown())
        ExitWindowsEx(EWX_POWEROFF, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED);
}

/* The following function is almost a direct copy of
  the example presented on
  http://msdn.microsoft.com/en-us/library/aa446619(v=VS.85).aspx
  */
BOOL SetPrivilege(
        HANDLE hToken,          // access token handle
        LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
        BOOL bEnablePrivilege   // to enable or disable privilege
        )
{
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if ( !LookupPrivilegeValue(
             NULL,            // lookup privilege on local system
             lpszPrivilege,   // privilege to lookup
             &luid ) )        // receives LUID of privilege
    {
        //Log::error(Log::Power, 0, "LookupPrivilegeValue error: " + GetLastError());
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege)
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
        tp.Privileges[0].Attributes = 0;

    // Enable the privilege or disable all privileges.

    if ( !AdjustTokenPrivileges(
             hToken,
             FALSE,
             &tp,
             sizeof(TOKEN_PRIVILEGES),
             (PTOKEN_PRIVILEGES) NULL,
             (PDWORD) NULL) )
    {
        //Log::error(Log::Power, 0, "AdjustTokenPrivilegesError: " + GetLastError());
        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)

    {
        //Log::error(Log::Power, 0, "The token does not have the specified privilege.");
        return FALSE;
    }

    return TRUE;
}

#endif
