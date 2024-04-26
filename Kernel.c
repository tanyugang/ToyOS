#include "Memory.h"

UINT64 KernelStart(BOOT_CONFIG *BootConfig)
{  
    UINT64 PassBack = 0;


    VideoInitial(BootConfig);

    ShellInitial();

    //MemInitial(BootConfig);

    int i = 0x2C;
    MADT *Madt = (MADT *)BootConfig->MadtAddress;
    
    while(i < Madt->Header.Length)
    {
        UINT8 *EntryType = ((UINT8 *)BootConfig->MadtAddress) + i;
        PrintStr("EntryType:");
        PrintDec(*EntryType);
       if(*EntryType == 0)
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
    }
    
    /*switch(*EntryType)
    {
    case 0:
        PrintStr("LAPIC ID:");
        LAPIC *Lapic = (LAPIC *)EntryType;
        PrintDec(Lapic->LapicID);
        PrintEnter();
        i += Lapic->Entry.RecordLength;
        break;
    case 1:
        PrintStr("I/O APIC ID:");
        IOAPIC *Ioapic = (IOAPIC *)EntryType;
        PrintDec(Ioapic->IopaicID);
        PrintEnter();
        i += Ioapic->Entry.RecordLength;
        break;
    case 2:
        PrintStr("IRQ Source:");
        ISO *Iso = (ISO *)EntryType;
        PrintDec(Iso->IrqSourece);
        PrintEnter();
        i += Iso->Entry.RecordLength;
        break;
    case 4:
        PrintStr("ACPI Processor ID:");
        NMI * Nmi = (NMI *)EntryType;
        PrintDec(Nmi->AcpiProcessorID);
        PrintEnter();
        i += Nmi->Entry.RecordLength;
        break;
    case 5:
        i += 0xC;
        break;

    }*/
    while(1);
    return PassBack;
}
    
    