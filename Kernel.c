#include "Kernel.h"

UINT64 KernelStart(BOOT_CONFIG *BootConfig)
{  
    UINT64 PassBack = 0;

    VideoInitial(BootConfig);
    ShellInitial();

    char String[20];
    String[0] = 'H';
    String[1] = 'E';
    String[2] = 'X';
    String[3] = '\n';
    String[4] = '\0';
    PrintStr(String);
    PrintHex(0x1234567890ABCDEF);
    String[0] = '\n';
    String[1] = 'D';
    String[2] = 'E';
    String[3] = 'C';
    String[4] = '\n';
    String[5] = '\0';
    PrintStr(String);

    PrintDec(1234567890);
    return PassBack;
}
    //PrintHex(0x1234567890ABCDEF);
    //PrintDec(Len);
    /*while (1)
    {
        ;
    }
    
    return PassBack;
}*/