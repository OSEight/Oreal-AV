

NTSTATUS PsSetCreateProcessNotifyRoutineEx(
  _In_  PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
  _In_  BOOLEAN Remove
);
VOID CreateProcessNotifyEx(
  _Inout_   PEPROCESS Process,
  _In_      HANDLE ProcessId,
  _In_opt_  PPS_CREATE_NOTIFY_INFO CreateInfo
);
typedef struct _PS_CREATE_NOTIFY_INFO {
  SIZE_T              Size;
  union {
    ULONG  Flags;
    struct {
      ULONG FileOpenNameAvailable  :1;
      ULONG Reserved  :31;
    };
  };
  HANDLE              ParentProcessId;
  CLIENT_ID           CreatingThreadId;
  struct _FILE_OBJECT  *FileObject;
  PCUNICODE_STRING    ImageFileName;
  PCUNICODE_STRING    CommandLine;
  NTSTATUS            CreationStatus;
} PS_CREATE_NOTIFY_INFO, *PPS_CREATE_NOTIFY_INFO;
NTSTATUS PsSetCreateThreadNotifyRoutine(
  _In_  PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
);
VOID
(*PCREATE_THREAD_NOTIFY_ROUTINE) (
    IN HANDLE  ProcessId,
    IN HANDLE  ThreadId,
    IN BOOLEAN  Create
    );
    NTSTATUS PsSetLoadImageNotifyRoutine(
  _In_  PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
);
VOID
  (*PLOAD_IMAGE_NOTIFY_ROUTINE)(
    __in_opt PUNICODE_STRING  FullImageName,
    __in HANDLE  ProcessId,
    __in PIMAGE_INFO  ImageInfo
    );
typedef struct  _IMAGE_INFO {
    union {
        ULONG  Properties;
        struct {
            ULONG ImageAddressingMode  : 8; //code addressing mode
            ULONG SystemModeImage      : 1; //system mode image
            ULONG ImageMappedToAllPids : 1; //mapped in all processes
            ULONG Reserved             : 22;
        };
    };
    PVOID  ImageBase;
    ULONG  ImageSelector;
    ULONG  ImageSize;
    ULONG  ImageSectionNumber;
} IMAGE_INFO, *PIMAGE_INFO;
FLT_PREOP_CALLBACK_STATUS    PreOperationCallback    (__inout    PFLT_CALLBACK_DATA    Data,    
    __in    PCFLT_RELATED_OBJECTS    FltObjects,    
    __deref_out_opt    PVOID    *CompletionContext)
{
    ...

    if    (    all_good    )
    {
        return    FLT_PREOP_SUCCESS_NO_CALLBACK;
    }
    else
    {
        //    Access    denied                
        Data-&gt;IoStatus.Information    =    0;
        Data-&gt;IoStatus.Status    =    STATUS_ACCESS_DENIED;
        return    FLT_PREOP_COMPLETE;
    }    
}
NTSTATUS CmRegisterCallbackEx(
_In_        PEX_CALLBACK_FUNCTION Function,
_In_        PCUNICODE_STRING Altitude,
_In_        PVOID Driver,
_In_opt_    PVOID Context,
_Out_       PLARGE_INTEGER Cookie,
_Reserved_  PVOID Reserved
);
EX_CALLBACK_FUNCTION RegistryCallback;

NTSTATUS RegistryCallback(
  _In_      PVOID CallbackContext,
  _In_opt_  PVOID Argument1,
  _In_opt_  PVOID Argument2
)
{ ... }

Argument1 = typedef enum _REG_NOTIFY_CLASS {
  RegNtDeleteKey,
  RegNtPreDeleteKey = RegNtDeleteKey,
...

Argument2 = typedef struct _REG_POST_OPERATION_INFORMATION {
  PVOID    Object;
  NTSTATUS Status;
  PVOID    PreInformation;
  NTSTATUS ReturnStatus;
  PVOID    CallContext;
  PVOID    ObjectContext;
  PVOID    Reserved;
} REG_POST_OPERATION_INFORMATION, *PREG_POST_OPERATION_INFORMATION;
NTSTATUS ObRegisterCallbacks(
  _In_   POB_CALLBACK_REGISTRATION CallBackRegistration,
  _Out_  PVOID *RegistrationHandle
);
typedef struct _OB_CALLBACK_REGISTRATION {
  USHORT                    Version;
  USHORT                    OperationRegistrationCount;
  UNICODE_STRING            Altitude;
  PVOID                     RegistrationContext;
  OB_OPERATION_REGISTRATION *OperationRegistration;
} OB_CALLBACK_REGISTRATION, *POB_CALLBACK_REGISTRATION;
typedef struct _OB_OPERATION_REGISTRATION {
  POBJECT_TYPE                *ObjectType;
  OB_OPERATION                Operations;
  POB_PRE_OPERATION_CALLBACK  PreOperation;
  POB_POST_OPERATION_CALLBACK PostOperation;
} OB_OPERATION_REGISTRATION, *POB_OPERATION_REGISTRATION;
VOID ObjectPostCallback(
  _In_  PVOID RegistrationContext,
  _In_  POB_POST_OPERATION_INFORMATION OperationInformation
);
typedef struct _OB_POST_OPERATION_INFORMATION {
  OB_OPERATION                  Operation;
  union {
    ULONG  Flags;
    struct {
      ULONG KernelHandle  :1;
      ULONG Reserved  :31;
    };
  };
  PVOID                         Object;
  POBJECT_TYPE                  ObjectType;
  PVOID                         CallContext;
  NTSTATUS                      ReturnStatus;
  POB_POST_OPERATION_PARAMETERS Parameters;
} OB_POST_OPERATION_INFORMATION, *POB_POST_OPERATION_INFORMATION;
typedef union _OB_POST_OPERATION_PARAMETERS {
  OB_POST_CREATE_HANDLE_INFORMATION    CreateHandleInformation;
  OB_POST_DUPLICATE_HANDLE_INFORMATION DuplicateHandleInformation;
} OB_POST_OPERATION_PARAMETERS, *POB_POST_OPERATION_PARAMETERS;
typedef struct _OB_POST_CREATE_HANDLE_INFORMATION {
  ACCESS_MASK GrantedAccess;
} OB_POST_CREATE_HANDLE_INFORMATION, *POB_POST_CREATE_HANDLE_INFORMATION;