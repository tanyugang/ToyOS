typedef void VOID;
typedef unsigned char UINT8;
typedef UINT8 CHAR8;
typedef unsigned int  UINT32;
typedef unsigned long long  UINT64;
typedef UINT64 UINTN;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

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
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS  VirtualStart;
    UINT64  Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct
{
    UINTN BufferSize;
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
} BMP_CONFIG;

typedef struct
{
    VIDEO_CONFIG VideoConfig;
    MEMORY_MAP   MemoryMap;
    BMP_CONFIG   AsciiBmp;
} BOOT_CONFIG;
#pragma pack()