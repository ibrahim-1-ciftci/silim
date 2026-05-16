#include <windows.h>
#include <winternl.h>

// Direct syscall for NtCreateThreadEx (x64)
typedef NTSTATUS (NTAPI *pNtCreateThreadEx)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, PVOID, PVOID, ULONG, SIZE_T, SIZE_T, SIZE_T, PVOID);

// Assembly stub for syscall
__declspec(naked) NTSTATUS NtCreateThreadExSyscall(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes,
    HANDLE ProcessHandle, PVOID StartRoutine, PVOID Argument, ULONG CreateFlags, SIZE_T ZeroBits, SIZE_T StackSize, SIZE_T MaximumStackSize, PVOID AttributeList) {
    __asm {
        mov r10, rcx
        mov eax, 0xC1 // Syscall number for NtCreateThreadEx (Windows 10 21H2)
        syscall
        ret
    }
}

HANDLE DirectSyscallCreateThread(PVOID start, PVOID arg) {
    HANDLE hThread = NULL;
    NTSTATUS status = NtCreateThreadExSyscall(&hThread, THREAD_ALL_ACCESS, NULL, GetCurrentProcess(), start, arg, 0, 0, 0, 0, NULL);
    if (status == 0) return hThread;
    return NULL;
}