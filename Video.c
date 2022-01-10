#include "Video.h"

BMP_CONFIG *AsciiBmp;
UINT32 *AsciiStart;
VIDEO_CONFIG *VideoConfig;
UINT32 *VideoStart;

int VideoInitial(BOOT_CONFIG *BootConfig)
{
    AsciiBmp = &BootConfig->AsciiBmp;
    AsciiStart = (UINT32 *)BootConfig->AsciiBmp.PixelStart;
    VideoConfig = &BootConfig->VideoConfig;
    VideoStart = (UINT32 *)BootConfig->VideoConfig.FrameBufferBase;

    BLOCK BackGround;

    {
    BackGround.Start.X = 0;
    BackGround.Start.Y = 0;
    BackGround.End.X = BootConfig->VideoConfig.HorizontalResolution - 1;
    BackGround.End.Y = BootConfig->VideoConfig.VerticalResolution - 1;
    BackGround.Color = 0xFF18679A;
    DrawBlock(BackGround);
    }
    return 0;
}

int DrawPixel(PIXEL Pixel)
{
    UINT32 *Position = VideoStart
                       + (Pixel.Y - 1) * VideoConfig->PixelsPerScanLine
                       + Pixel.X;   
    *Position = Pixel.Color;
     return 0;
}

int DrawBlock(BLOCK Block)
{
    PIXEL Pixel;
    Pixel.Color = Block.Color;
    for(int i = Block.Start.Y; i < Block.End.Y; i++)
    {
        for(int j = Block.Start.X; j < Block.End.X; j++)
        {
            Pixel.X = j;
            Pixel.Y = i;
            DrawPixel(Pixel);
        }
    }
    return 0;
}

int DrawLetter(UINT8 Ascii, POINT Destination)
{
    UINT8 Index = Ascii - 32;
    if(Ascii < 32 || Ascii > 126) // 0x20~0x7E
    {
        Index = 127 - 32;
    }
    UINT32 *From = AsciiStart + (Index % 32) * LetterWidth
                   + (Index / 32) * LetterHeight * AsciiBmp->Width;
    UINT32 *To = VideoStart + Destination.X
                 + Destination.Y * VideoConfig->PixelsPerScanLine;
    for(int i = 0; i < LetterHeight; i++)
    {
        for(int j = 0; j < LetterWidth; j++)
        {
            *To = *From;
            From++;
            To++;
        }
        From = From + AsciiBmp->Width - LetterWidth;
        To = To + VideoConfig->PixelsPerScanLine - LetterWidth;
    }
    return 0;
}