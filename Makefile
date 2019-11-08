# Build the kernel binary
#kernel.bin: kernel_entry.o kernel.o
#	ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary
# Build the kernel object file
#kernel.o : kernel.c
#	gcc -ffreestanding -c kernel.c -o kernel.o
# Build the kernel entry object file.
#kernel_entry.o : kernel_entry.asm
#	nasm kernel_entry.asm -f elf -o kernel_entry.o


# $^ is substituted with all of the target’s dependancy files


# Automatically generate lists of sources using wildcards. C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# TODO: Make sources dep on all header files.
# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}
# Defaul build target
all: os-image
# Run bochs to simulate booting of our code.
run: all 
	bochs
# This is the actual disk image that the computer loads,
# which is the combination of our compiled bootsector and kernel 
os-image: boot_sect.bin kernel.bin
	cat $^ > os-image
#This builds the binary of our kernel from two object files: - the kernel_entry, which jumps to main() in our kernel
#- the compiled C kernel
kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary
	
# Generic rule for compiling C code to an object file
# For simplicity, we C files depend on all header files. 
%.o : %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry.
%.o : %.asm
	nasm $< -f elf -o $@
%. bin : %. asm
	nasm $< -f bin -I ’../../16bit/’ -o $@
clean:
	rm -fr *.bin *.dis *.o os-image
	rm -fr kernel/*.o boot/*.bin drivers/*.o
	