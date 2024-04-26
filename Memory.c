#include "Memory.h"

int MemInitial(BOOT_CONFIG *BootConfig)
{
    EFI_MEMORY_DESCRIPTOR *EfiMemory = (EFI_MEMORY_DESCRIPTOR *)(BootConfig->MemoryMap.Buffer);
    
    /*for(int i = 0; i < 22; i++)
    {
        PrintHex(EfiMemory->Type);
        PrintSpace();
        PrintHex(EfiMemory->PhysicalStart);
        PrintSpace();
        PrintHex(EfiMemory->VirtualStart);
        PrintSpace();
        PrintHex(EfiMemory->NumberOfPages);
        PrintSpace();
        PrintHex(EfiMemory->Attribute);
        PrintEnter();
        EfiMemory++;
    }

    char *MemDesc = (char *)(BootConfig->MemoryMap.Buffer);
    PrintHex((UINT64)(BootConfig->MemoryMap.Buffer));
    PrintSpace();
    PrintDec(BootConfig->MemoryMap.DescriptorSize);
    PrintEnter();     

    for(int i = 0; i < BootConfig->MemoryMap.DescriptorSize; i++)
    {
        PrintByte(*MemDesc);
        if(i != 0 && (i + 1) % 8 == 0)
        {
            PrintEnter();
        }

        MemDesc++;
    }


    for(int i = 0; i < 22; i++)
    {
        PrintHex(EfiMemory->Type);
        PrintSpace();
        PrintHex(EfiMemory->PhysicalStart);
        PrintSpace();
        PrintHex(EfiMemory->VirtualStart);
        PrintSpace();
        PrintHex(EfiMemory->NumberOfPages);
        PrintSpace();
        PrintHex(EfiMemory->Attribute);
        PrintEnter();
        EfiMemory++;
    }*/
    
    OS_MEMORY_DESCRIPTOR *OsMemory = NULL;
    // Find some space for OSMemory table, should be bigger than EfiMemroy table
    int EfiMemoryPageSize = (BootConfig->MemoryMap.MapSize >> 12) + 1;
    //PrintDec(EfiMemoryPageSize);
    //PrintSpace();
    EFI_PHYSICAL_ADDRESS OsMemoryAddress = 0;
    int EfiDescriptorCount = BootConfig->MemoryMap.MapSize / BootConfig->MemoryMap.DescriptorSize;
    for(int i = 0; i < EfiDescriptorCount; i++)
    {
        if(EfiMemoryPageSize < EfiMemory[i].NumberOfPages && EfiMemory[i].Type == 7)
        {
            OsMemoryAddress = EfiMemory[i].PhysicalStart;
            OsMemory = (OS_MEMORY_DESCRIPTOR *)OsMemoryAddress;
            break;
        }
    }


    //PrintHex((UINT64)OsMemory);
    //PrintSpace();
    int OsMemDescNum = 0;
    for(int i = 0; i < EfiDescriptorCount; i++)
    {
        if(EfiMemory[i].Type == EfiBootServicesCode
           || EfiMemory[i].Type == EfiBootServicesData
           || EfiMemory[i].Type == EfiConventionalMemory)
        {
            OsMemory->Type = FREE_MEMORY;
        }
        else if(EfiMemory[i].Type == EfiMemoryMappedIO)
        {
            OsMemory->Type = MMIO_MEMORY;
        }
        else
        {
            OsMemory->Type = UEFI_MEMORY;
        }
        OsMemory->PhysicalStart = EfiMemory[i].PhysicalStart;
        OsMemory->PageSize = EfiMemory[i].NumberOfPages;

        if(i > 0 && OsMemory->Type == (OsMemory-1)->Type)
        {
            if(OsMemory->PhysicalStart == (OsMemory-1)->PhysicalStart + ((OsMemory-1)->PageSize << 12))
            {
                (OsMemory-1)->PageSize += OsMemory->PageSize;
                continue;
            }
        }
        OsMemory++;
        OsMemDescNum++;
    }


    PrintDec(EfiDescriptorCount);
    PrintSpace();
    PrintDec(OsMemDescNum);
    PrintEnter();
    
    OsMemory = (OS_MEMORY_DESCRIPTOR *)OsMemoryAddress;
    UINT64 TotalMemory = 0;
    for(int i = 0; i < OsMemDescNum; i++)
    {
        PrintDec(OsMemory->Type);
        PrintSpace();
        PrintHex(OsMemory->PhysicalStart);
        PrintSpace();
        PrintHex(OsMemory->PageSize);
        PrintEnter();
        if(OsMemory->Type != MMIO_MEMORY)
        {
            TotalMemory += OsMemory->PageSize;
        }
        OsMemory++;
    }


    char HeadToPrint[8];
    HeadToPrint[0] = 'T';
    HeadToPrint[1] = 'o';
    HeadToPrint[2] = 't';
    HeadToPrint[3] = 'a';
    HeadToPrint[4] = 'l';
    HeadToPrint[5] = ':';
    HeadToPrint[6] = ' ';
    HeadToPrint[7] = '\0';
    char TailToPrint[4];
    TailToPrint[0] = 'M';
    TailToPrint[1] = 'B';
    TailToPrint[2] = '\n';
    TailToPrint[3] = '\0';
    PrintStr(HeadToPrint);
    PrintDec(TotalMemory >> 8);
    PrintSpace();
    PrintStr(TailToPrint);
    return 0;
}
