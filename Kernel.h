#include "Memory.h"

#pragma pack(1)
typedef struct GDT_SELECTOR
{
    UINT16 LimitLow;
    UINT16 BaseLow;
    UINT8  BaseMiddle;
    UINT8  AccessByte;
    UINT8  LimitAndFlags;
    UINT8  BaseHigh;
} GDT_DESCRIPTOR;

typedef struct GDT
{
    GDT_DESCRIPTOR Descriptor[3];
    UINT16 Length;
    EFI_PHYSICAL_ADDRESS Address;
} GDT;
#pragma pack()