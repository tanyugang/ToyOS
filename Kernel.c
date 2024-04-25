#include "Memory.h"

UINT64 KernelStart(BOOT_CONFIG *BootConfig)
{  
    UINT64 PassBack = 0;


    VideoInitial(BootConfig);
    ShellInitial();
    /*PrintDec(BootConfig->ProcessorCount);
    PrintSpace();
    for(int i = 0; i < BootConfig->ProcessorCount; i++)
    {
        PrintDec(BootConfig->LapicID[i]);
        PrintSpace();
    }*/
    MemInitial(BootConfig);
    PrintHex(BootConfig->MadtAddress);
    PrintEnter();
    int i = 0x2C;
    MADT *Madt = (MADT *)BootConfig->MadtAddress;

    while(i < Madt->Header.Length)
    {
        UINT8 *EntryType = ((UINT8 *)BootConfig->MadtAddress) + i;
        PrintStr("EntryType:");
        PrintDec(*EntryType);
       /* if(*EntryType == 0)
        {
            LAPIC *Lapic = (LAPIC *)EntryType;
            PrintStr(" ACPI Processor ID:");
            PrintDec(Lapic->LapicID);
            PrintEnter();
            i += Lapic->Entry.RecordLength;
        } else if (*EntryType == 1)
        {
            IOAPIC *Ioapic = (IOAPIC *)EntryType;
            PrintStr(" I/O APIC ID:");
            PrintDec(Ioapic->IopaicID);
            PrintEnter();
            i += Ioapic->Entry.RecordLength;
        } else if (*EntryType == 2)
        {
            ISO *Iso = (ISO *)EntryType;
            PrintStr(" IRQ Source:");
            PrintDec(Iso->IrqSourece);
            PrintEnter();
            i += Iso->Entry.RecordLength;
        } else if (*EntryType == 4)
        {
            NMI * Nmi = (NMI *)EntryType;
            PrintStr(" ACPI Processor ID:");
            PrintDec(Nmi->AcpiProcessorID);
            PrintEnter();
            i += Nmi->Entry.RecordLength;
        } else if(*EntryType == 5)
        {
            i += 0xC;
        }
    }*/
    switch(*EntryType)
    {
    case 0:
        LAPIC *Lapic = (LAPIC *)EntryType;
        PrintStr("ACPI Processor ID:");
        PrintDec(Lapic->LapicID);
        PrintEnter();
        i += Lapic->Entry.RecordLength;
        break;
    case 1:
        IOAPIC *Ioapic = (IOAPIC *)EntryType;
        PrintStr("I/O APIC ID:");
        PrintDec(Ioapic->IopaicID);
        PrintEnter();
        i += Ioapic->Entry.RecordLength;
        break;
    case 2:
        ISO *Iso = (ISO *)EntryType;
        PrintStr("IRQ Source:");
        PrintDec(Iso->IrqSourece);
        PrintEnter();
        i += Iso->Entry.RecordLength;
        break;
    case 4:
        NMI * Nmi = (NMI *)EntryType;
        PrintStr("ACPI Processor ID:");
        PrintDec(Nmi->AcpiProcessorID);
        PrintEnter();
        i += Nmi->Entry.RecordLength;
        break;
    case 5:
        i += 0xC;
        break;

    }
    
    while(1);
    //MemInitial(BootConfig);
    //while(1);
    /*char String[20];
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

    PrintDec(1234567890);*/
    return PassBack;
}