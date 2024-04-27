#include "Video.h"

BMP_CONFIG *AsciiBmp;
UINT32 *AsciiStart;
VIDEO_CONFIG *VideoConfig;
UINT32 *VideoStart;
RESOLUTION Resolution;

int VideoInitial(BOOT_CONFIG *BootConfig)
{
    AsciiBmp = &BootConfig->AsciiBmp;
    AsciiStart = (UINT32 *)BootConfig->AsciiBmp.PixelStart;
    VideoConfig = &BootConfig->VideoConfig;
    VideoStart = (UINT32 *)BootConfig->VideoConfig.FrameBufferBase;
    Resolution.Horizontal = BootConfig->VideoConfig.HorizontalResolution;
    Resolution.Vertical = BootConfig->VideoConfig.VerticalResolution;
    return 0;
}

int DrawFont()
{
    UINT32 *From = AsciiStart;
    UINT32 *To = VideoStart;
    for(int i = 0; i < 640 * 108; i++)
    {
        *To = *From;
        From++;
        To++;
        if((i+1) % 640 == 0)
            To = To + VideoConfig->PixelsPerScanLine - 640;
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
    UINT8 Index = Ascii - InVisiable;
    if(Ascii < 32 || Ascii > 126) // 0x20~0x7E之外的字符，不可见，以波浪线代替
    {
        Index = 95;//
    }
    UINT32 *From = AsciiStart + (Index % LetterOneRow) * LetterWidth
                   + (Index / LetterOneRow) * LetterHeight * AsciiBmp->Width;
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