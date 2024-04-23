clang Kernel.c Video.c Shell.c Memory.c -c -nostdlib -ffreestanding 
ld.lld Kernel.o Video.o Shell.o Memory.o -e KernelStart -o Kernel.elf
cp $HOME/ToyOS/OS/Kernel.elf $HOME/ToyOS/OVMF/ESP/Kernel.elf
qemu-system-x86_64 -m 4096 -drive if=pflash,format=raw,file=$HOME/ToyOS/OVMF/OVMF_CODE.fd,readonly=on -drive if=pflash,format=raw,file=$HOME/ToyOS/OVMF/OVMF_VARS.fd,readonly=on -drive format=raw,file=fat:rw:$HOME/ToyOS/OVMF/ESP -net none
