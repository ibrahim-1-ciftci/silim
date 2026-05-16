#include <windows.h>
#include <stdio.h>

void TakeScreenshot() {
    // Basit screenshot – GDI+ ile
    // Burada kısaca özet; tam implementation uzun
    MessageBoxA(NULL, "Screenshot alındı (demo)", "Module", MB_OK);
}

void OpenShell() {
    WinExec("cmd.exe", SW_HIDE);
}

void DownloadFile(char *url, char *dest) {
    // URLDownloadToFile
    // ...
}