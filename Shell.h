#include "Video.h"

#pragma pack(1)

typedef struct
{
    UINT32 Width;
    UINT32 Height;
    UINT32 X;
    UINT32 Y;
    UINT32 OutLines;
} SETUP;

typedef struct
{
    CHAR8 *Title;
    UINT32 Height;
    UINT32 Color;
} HEAD;


typedef struct
{
    UINT32 Row;
    UINT32 Col;
    POINT Start;
    POINT Pos;
} CURSOR;

typedef struct
{
    SETUP Setup;
    HEAD Head;
    CURSOR Cursor;
} BASE;


#pragma pack()

int ShellInitial();
int SetCursor(UINT8 Count);
int PrintHex(UINT64 Number);
int PrintDec(UINT64 Number);
int PrintStr(char *String);
