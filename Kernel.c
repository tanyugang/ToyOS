#include "Kernel.h"

UINT64 KernelStart(BOOT_CONFIG *BootConfig)
{  
    UINT64 PassBack = 0;

    VideoInitial(BootConfig);
    ShellInitial();

    MemInitial(BootConfig);
    while (1)
    {
        ;
    }
    
    return PassBack;
}
