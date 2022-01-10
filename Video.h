#include "Uefi.h"

#define LetterWidth 20
#define LetterHeight 36
#pragma pack(1)

typedef struct
{
    UINT32 X;
    UINT32 Y;
} POINT;

typedef struct
{
    UINT32 X;
    UINT32 Y;
    UINT32 Color;
} PIXEL;

typedef struct
{
    POINT Start;
    POINT End;
    UINT32 Color;
} BLOCK;

typedef struct
{
    UINT32 *Start;
    UINT32 Width;
    UINT32 Height;
}ASCII_BMP;
#pragma pack()

int VideoInitial(BOOT_CONFIG *BootConfig);
int DrawPixel(PIXEL Pixel);
int DrawBlock(BLOCK Block);

int DrawLetter(UINT8 Index, POINT Destination);
int DrawBmp(BOOT_CONFIG BootConfig);


