#include "Kernel.h"
int LoadGDT();

UINT64 KernelStart(BOOT_CONFIG *BootConfig)
{  
    UINT64 PassBack = 0;


    VideoInitial(BootConfig);

    ShellInitial();
    
    LoadGDT();
    MemInitial(BootConfig);
    /*while(1);
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
    
    switch(*EntryType)
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

    
    BOOLEAN Enabled;
    BOOLEAN Pending;
    EFI_TIME WakeupTime;
    EFI_RUNTIME_SERVICES *RunTimeServices = BootConfig->RunTimeServices;
    RunTimeServices->GetWakeupTime(&Enabled, &Pending, &WakeupTime);
    PrintDec(WakeupTime.Year);
    PrintSpace();

    EFI_STATUS Status;
    EFI_TIME CurrentTime;
    EFI_TIME_CAPABILITIES CurrentTimeCap;
    Status = BootConfig->RunTimeServices->GetTime(&CurrentTime, NULL);
    PrintHex(Status);
    PrintSpace();
    PrintDec(CurrentTime.Year);
    PrintSpace();
    PrintDec(CurrentTime.Month);
    PrintSpace();
    PrintDec(CurrentTime.Day);
    PrintSpace();
    PrintDec(CurrentTime.Hour);
    PrintSpace();
    PrintDec(CurrentTime.Minute);
    PrintSpace();
    PrintDec(CurrentTime.Second);
    PrintSpace();
    PrintDec(CurrentTime.Nanosecond);
    PrintSpace();
    BootConfig->RunTimeServices->ResetSystem(EfiResetShutdown, 0, 4096, NULL);
    while(1);
    return PassBack;
}

int LoadGDT()
{
    GDT Gdt;
    // NULL Descriptior
    Gdt.Descriptor[0].LimitLow = 0xFFFF;
    Gdt.Descriptor[0].BaseLow = 0;
    Gdt.Descriptor[0].BaseMiddle = 0;
    Gdt.Descriptor[0].AccessByte = 0x9B;
    Gdt.Descriptor[0].LimitAndFlags = 0xCF;
    Gdt.Descriptor[0].BaseHigh = 0xFF;
    // Kernel Code Segment
    Gdt.Descriptor[1].LimitLow = 0xFFFF;
    Gdt.Descriptor[1].BaseLow = 0;
    Gdt.Descriptor[1].BaseMiddle = 0;
    Gdt.Descriptor[1].AccessByte = 0x9B;
    Gdt.Descriptor[1].LimitAndFlags = 0xCF;
    Gdt.Descriptor[1].BaseHigh = 0xFF;

    // Kernel Data Segment
    Gdt.Descriptor[2].LimitLow = 0xFFFF;
    Gdt.Descriptor[2].BaseLow = 0;
    Gdt.Descriptor[2].BaseMiddle = 0;
    Gdt.Descriptor[2].AccessByte = 0x93;
    Gdt.Descriptor[2].LimitAndFlags = 0xCF;
    Gdt.Descriptor[2].BaseHigh = 0xFF;
    // Access Byte
    // P DPL S E DC RW A
    // 1 00  1 1 0  1  1
    // 1 00  1 0 0  1  1
    Gdt.Length = (UINT64)&Gdt.Descriptor[2].BaseHigh - (UINT64)&Gdt;
    Gdt.Address = (EFI_PHYSICAL_ADDRESS)&Gdt;

    asm("LGDT %0": :"m"(Gdt.Length));

    return 0;

}

    
    