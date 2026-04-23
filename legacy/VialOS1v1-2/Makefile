all:
	mkdir -p build
	mkdir -p build/iso/boot/grub

	nasm -f elf32 boot.s -o build/boot.o

	gcc -m32 -ffreestanding -c cork/cork.c -o build/cork.o
	gcc -m32 -ffreestanding -c cork/cpu/intrpts.c -o build/intrpts.o
	gcc -m32 -ffreestanding -c cork/cpu/io.c -o build/io.o
	gcc -m32 -ffreestanding -c cork/drivers/keybd.c -o build/keybd.o
	gcc -m32 -ffreestanding -c cork/drivers/vga.c -o build/vga.o

	gcc -m32 -ffreestanding -c vial/vial.c -o build/vial.o
	gcc -m32 -ffreestanding -c vial/shell/cmds.c -o build/cmds.o
	gcc -m32 -ffreestanding -c vial/shell/vsh.c -o build/vsh.o

	ld -m elf_i386 -T memory.ld -o build/vialos.bin \
		build/boot.o \
		build/cork.o \
		build/intrpts.o \
		build/io.o \
		build/keybd.o \
		build/vga.o \
		build/vial.o \
		build/cmds.o \
		build/vsh.o

	cp build/vialos.bin build/iso/boot/
	cp iso/boot/grub/grub.cfg build/iso/boot/grub/

	grub-mkrescue -o build/VialOS1v1-2.iso build/iso

clean:
	rm -rf build