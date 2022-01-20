#include "Shell.h"

#define FREE_MEMORY 0
#define OS_CODE 1
#define OS_DATA 2
#define AP_CODE 3
#define AP_DATA 4
#define UEFI_MEMORY 11
#define MMIO_MEMORY 12

#pragma pack(1)
typedef struct
{
    UINT32 Type;
    UINT64 PhysicalStart;
    UINT64 PageSize; 
}OS_MEMORY_DESCRIPTOR;

#pragma pack()


int MemInitial(BOOT_CONFIG *BootConfig);