#include "Shell.h"

BASE Base;
UINT16 MaxCol = 0;
UINT16 MaxRow = 0;

int ShellInitial()
{
    MaxCol = Resolution.Horizontal / LetterWidth;
    MaxRow = Resolution.Vertical / LetterHeight;
 
    BLOCK BackGround;
    {
    BackGround.Start.X = 0;
    BackGround.Start.Y = 0;
    BackGround.End.X = Resolution.Horizontal - 1;
    BackGround.End.Y = Resolution.Vertical - 1;
    BackGround.Color = 0x00000000;
    DrawBlock(BackGround);
    }
    SetCursor(0);
    PrintStr("Horizotal: ");
    PrintDec(Resolution.Horizontal);
    PrintStr("\nVertical: ");
    PrintDec(Resolution.Vertical);
    PrintStr("\nMaxCol: ");
    PrintDec(MaxCol);
    PrintStr("\nMaxRow: ");
    PrintDec(MaxRow);
    return 0;
}

int SetCursor(UINT8 Count)
{
    Base.Cursor.Col += Count;
    if(Base.Cursor.Col >= MaxCol)
    {
        Base.Cursor.Row += Base.Cursor.Col / MaxCol;
        Base.Cursor.Col = Base.Cursor.Col % MaxCol;
    }
    Base.Cursor.Pos.X = Base.Cursor.Start.X + Base.Cursor.Col * LetterWidth;
    Base.Cursor.Pos.Y = Base.Cursor.Start.Y + Base.Cursor.Row * LetterHeight;
    BLOCK Cursor;
    Cursor.Color = 0xFFFFFFFF;
    Cursor.Start.X = Base.Cursor.Pos.X + 1;
    Cursor.Start.Y = Base.Cursor.Pos.Y + 30;
    Cursor.End.X = Cursor.Start.X + 18;
    Cursor.End.Y = Cursor.Start.Y + 3;
    DrawBlock(Cursor);

    return 0;
}

int PrintHex(UINT64 Number)
{
    UINT64 Trans = Number;

    DrawLetter('0', Base.Cursor.Pos);
    SetCursor(1);
    DrawLetter('x', Base.Cursor.Pos);
    SetCursor(1);

    char Hex[16];
    int  Len = 0;
    for(int i = 0; i < 16; i++)
    {
        Hex[i] = Trans & 0xF;
        if(Hex[i] >= 0 && Hex[i] <= 9)
        {
            Hex[i] += 48;
        }
        if(Hex[i] > 9 && Hex[i] < 16)
        {
            Hex[i] += 55;
        }
        Trans = Trans >> 4;
        Len++;
        if(Trans == 0)
        {
            break;
        }
    }

    for(int j = 0; j < Len; j++)
    {
        DrawLetter(Hex[Len-j-1], Base.Cursor.Pos);
        SetCursor(1);
    }  
    return 0;
}

int PrintDec(UINT64 Number)
{
    char Dec[20];
    UINT8 Len = 0;
    UINT64 Trans = Number;
    for(int i = 0; i < 20; i++)
    {
        Dec[i] = (Trans % 10) + 48;
        Trans = Trans / 10;
        Len++;
        if(Trans == 0)
        {
            break;
        }  
    }

    for(int j = 0; j < Len; j++)
    {
        DrawLetter(Dec[Len-j-1], Base.Cursor.Pos);
        SetCursor(1);
    }

    return Len;
}

int PrintStr(char *String)
{
    char *ToPrint = String;
    int Len = 0;
    while (*ToPrint != '\0')
    {
        Len++;
        ToPrint++;
    }

    for(int i = 0; i < Len; i++)
    {
        if(String[i] == '\n')
        {
            DrawLetter(' ', Base.Cursor.Pos);
            SetCursor(MaxCol - Base.Cursor.Col);
            continue;
        }
        DrawLetter(String[i], Base.Cursor.Pos);
        SetCursor(1);    
    }   
    return 0;
}

int PrintEnter()
{
    DrawLetter(' ', Base.Cursor.Pos);
    SetCursor(MaxCol - Base.Cursor.Col);
    return 0;
}

int PrintSpace()
{
    DrawLetter(' ', Base.Cursor.Pos);
    SetCursor(1);
    return 0;
}

int PrintByte(UINT8 Number)
{
    UINT8 Trans = Number;
    char Hex[2];
    for(int i = 0; i < 2; i++)
    {
        Hex[i] = Trans & 0xF;
        if(Hex[i] >= 0 && Hex[i] <= 9)
        {
            Hex[i] += 48;
        }
        if(Hex[i] > 9 && Hex[i] < 16)
        {
            Hex[i] += 55;
        }
        Trans = Trans >> 4;
    }

    for(int j = 0; j < 2; j++)
    {
        DrawLetter(Hex[2-j-1], Base.Cursor.Pos);
        SetCursor(1);
    }  
    return 0;
}