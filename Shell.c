#include "Shell.h"

BASE Base;

int ShellInitial()
{
    Base.Setup.Height = 860;
    Base.Setup.Width = 1400;
    Base.Setup.X = 20;
    Base.Setup.Y = 20;
    Base.Setup.OutLines = 1;

    Base.Cursor.Row = 0;// Max 69
    Base.Cursor.Col = 0;// Max 22
    Base.Cursor.Start.X = 30;
    Base.Cursor.Start.Y = 78;
    Base.Cursor.Pos.X = Base.Cursor.Start.X;
    Base.Cursor.Pos.Y = Base.Cursor.Start.Y;

    // Draw  Background
    BLOCK BackGround;
    BackGround.Color = 0x00000000;
    BackGround.Start.X =  20;
    BackGround.Start.Y = 20;
    BackGround.End.X = 1420;
    BackGround.End.Y = 880;
    DrawBlock(BackGround);


    if(Base.Setup.OutLines)
    {    
        // Draw OutLine Up
        BLOCK OutLine;
        OutLine.Color = 0xFFFFFFFF;
        OutLine.Start.X =  20;
        OutLine.Start.Y = 20;
        OutLine.End.X = 1420;
        OutLine.End.Y = 22;
        DrawBlock(OutLine);

        // Draw OutLine Middle
        OutLine.Start.X =  22;
        OutLine.Start.Y = 68;
        OutLine.End.X = 1418;
        OutLine.End.Y = 70;
        DrawBlock(OutLine);

        // Draw OutLine Down
        OutLine.Start.X =  20;
        OutLine.Start.Y = 878;
        OutLine.End.X = 1420;
        OutLine.End.Y = 880;
        DrawBlock(OutLine);

        // Draw OutLine Left
        OutLine.Start.X =  20;
        OutLine.Start.Y = 22;
        OutLine.End.X = 22;
        OutLine.End.Y = 878;
        DrawBlock(OutLine);

        // Draw OutLine right
        OutLine.Start.X =  1418;
        OutLine.Start.Y = 22;
        OutLine.End.X = 1420;
        OutLine.End.Y = 878;
        DrawBlock(OutLine);
    }

    POINT Dest;
    Dest.X = 30;
    Dest.Y = 78;
    //DrawLetter('T', Dest);


    Base.Head.Title[0] = 'T';
    Base.Head.Title[1] = 'o';
    Base.Head.Title[2] = 'y';
    Base.Head.Title[3] = 'O';
    Base.Head.Title[4] = 'S';

    POINT TitleStart;
    TitleStart.X = (Base.Setup.Width - 20 * 5) / 2 + 22;
    TitleStart.Y = (46 - 36) / 2 + 22;

    for(int i = 0; i < 5; i++)
    {
        DrawLetter(Base.Head.Title[i], TitleStart);
        TitleStart.X += 20;
    }

    SetCursor(0);
    return 0;
}

int SetCursor(UINT8 Count)
{
    Base.Cursor.Col += Count;
    if(Base.Cursor.Col >= 69)
    {
        Base.Cursor.Row += Base.Cursor.Col / 69;
        Base.Cursor.Col = Base.Cursor.Col % 69;
    }
    Base.Cursor.Pos.X = Base.Cursor.Start.X + Base.Cursor.Col * 20;
    Base.Cursor.Pos.Y = Base.Cursor.Start.Y + Base.Cursor.Row * 36;
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
            SetCursor(69-Base.Cursor.Col);
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
    SetCursor(69-Base.Cursor.Col);
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