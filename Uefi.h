typedef void VOID;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef UINT8 CHAR8;
typedef unsigned int  UINT32;
typedef unsigned long long  UINT64;
typedef UINT64 UINTN;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;
#define NULL ((VOID *) 0);

typedef enum {
  /// Not used.
  EfiReservedMemoryType,
  /// The code portions of a loaded application.
  /// (Note that UEFI OS loaders are UEFI applications.)
  EfiLoaderCode,
  /// The data portions of a loaded application and the default data allocation
  /// type used by an application to allocate pool memory.
  EfiLoaderData,
  /// The code portions of a loaded Boot Services Driver.
  EfiBootServicesCode,
  /// The data portions of a loaded Boot Serves Driver, and the default data
  /// allocation type used by a Boot Services Driver to allocate pool memory.
  EfiBootServicesData,
  /// The code portions of a loaded Runtime Services Driver.
  EfiRuntimeServicesCode,
  /// The data portions of a loaded Runtime Services Driver and the default
  /// data allocation type used by a Runtime Services Driver to allocate pool memory.
  EfiRuntimeServicesData,
  /// Free (unallocated) memory.
  EfiConventionalMemory,
  /// Memory in which errors have been detected.
  EfiUnusableMemory,
  /// Memory that holds the ACPI tables.
  EfiACPIReclaimMemory,
  /// Address space reserved for use by the firmware.
  EfiACPIMemoryNVS,
  /// Used by system firmware to request that a memory-mapped IO region
  /// be mapped by the OS to a virtual address so it can be accessed by EFI runtime services.
  EfiMemoryMappedIO,
  /// System memory-mapped IO region that is used to translate memory
  /// cycles to IO cycles by the processor.
  EfiMemoryMappedIOPortSpace,
  /// Address space reserved by the firmware for code that is part of the processor.
  EfiPalCode,
  /// A memory region that operates as EfiConventionalMemory,
  /// however it happens to also support byte-addressable non-volatility.
  EfiPersistentMemory,
  EfiMaxMemoryType
} EFI_MEMORY_TYPE;
#pragma pack(1)
typedef struct
{
  UINT8 Blue;
  UINT8 Green;
  UINT8 Red;
  UINT8 Reserved;
} BGR_PIXEL;

typedef struct
{
    EFI_PHYSICAL_ADDRESS       FrameBufferBase;
    UINT64                      FrameBufferSize;
    UINT32                     HorizontalResolution;
    UINT32                     VerticalResolution;
    UINT32                     PixelsPerScanLine;
} VIDEO_CONFIG;

typedef struct
{
    UINT32  Type;
    UINT32  ReservedA;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS  VirtualStart;
    UINT64  NumberOfPages;
    UINT64  Attribute;
    UINT64  ReservedB;
} EFI_MEMORY_DESCRIPTOR;

typedef struct
{
    VOID *Buffer;
    UINTN MapSize;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
} MEMORY_MAP;

typedef struct
{
    UINTN Size;
    UINTN PageSize;
    UINTN Width;
    UINTN Height;
    UINTN Offset;
    UINT64 PixelStart;
    UINT64 BitsPerPx;
} BMP_CONFIG;

typedef struct SDT_HEADER
{
    CHAR8 Signature[4];
    UINT32 Length;
    UINT8 Revision;
    UINT8 CheckSum;
    CHAR8 OEMID[6];
    CHAR8 TableID[8];
    UINT32 OEMRevision;
    UINT32 CreatorID;
    UINT32 CreatorRevision;
} SDT_HEADER;

typedef struct MADT
{
    SDT_HEADER Header;
    UINT32 LapicAddress;
    UINT32 Flags;
} MADT;

typedef struct MADT_ENTRY
{
    UINT8 EntryType;
    UINT8 RecordLength;
} MADT_ENTRY;

typedef struct LAPIC
{
    MADT_ENTRY Entry;
    UINT8 ProcessorID;
    UINT8 LapicID;
    UINT32 Flags;
} LAPIC;

typedef struct IOAPIC
{
    MADT_ENTRY Entry;
    UINT8 IopaicID;
    UINT8 Reserved;
    UINT32 IoapicAddress;
    UINT32 GlobalSystemInterruptBase;
} IOAPIC;

typedef struct ISO
{
    MADT_ENTRY Entry;
    UINT8 BusSource;
    UINT8 IrqSourece;
    UINT32 Gsi;
    UINT16 Flags;
} ISO;

typedef struct NMI
{
    MADT_ENTRY Entry;
    UINT8 AcpiProcessorID;
    UINT16 Flags;
    UINT8 Lint;
} NMI;

typedef struct
{
    VIDEO_CONFIG VideoConfig;
    MEMORY_MAP   MemoryMap;
    BMP_CONFIG   AsciiBmp;
    EFI_PHYSICAL_ADDRESS KernelEntryPoint;
    EFI_PHYSICAL_ADDRESS MadtAddress;
} BOOT_CONFIG;
#pragma pack()