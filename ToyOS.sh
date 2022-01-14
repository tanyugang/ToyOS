clang Kernel.c Video.c Shell.c -c -nostdlib -ffreestanding 
ld.lld Kernel.o Video.o Shell.o -e KernelStart -o Kernel.elf
cp ~/CodingMaster/ToyOS/Kernel.elf ~/CodingMaster/OVMF/ESP/Kernel.elf
qemu-system-x86_64 -m 4096 -drive if=pflash,format=raw,file=/home/coding/CodingMaster/OVMF/OVMF_CODE.fd,readonly=on -drive if=pflash,format=raw,file=/home/coding/CodingMaster/OVMF/OVMF_VARS.fd,readonly=on -drive format=raw,file=fat:rw:/home/coding/CodingMaster/OVMF/ESP -net none
