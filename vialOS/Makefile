all:
	mkdir -p build
	mkdir -p build/iso/boot/grub

	nasm -f elf32 boot.s -o build/boot.o

	gcc -m32 -ffreestanding -c cork/cork.c -o build/cork.o

	gcc -m32 -ffreestanding -c cork/arch/i386/interrupts/interrupts.c -o build/interrupts.o
	gcc -m32 -ffreestanding -c cork/arch/i386/io/io.c -o build/io.o

	gcc -m32 -ffreestanding -c cork/drivers/keyboard/keyboard.c -o build/keyboard.o
	gcc -m32 -ffreestanding -c cork/drivers/vga/vga.c -o build/vga.o

	gcc -m32 -ffreestanding -c vial/vial.c -o build/vial.o

	gcc -m32 -ffreestanding -c vial/managers/graphics/graphics.c -o build/graphics.o
	gcc -m32 -ffreestanding -c vial/managers/typing/typing.c -o build/typing.o

	gcc -m32 -ffreestanding -c vial/vsh/vsh.c -o build/vsh.o
	gcc -m32 -ffreestanding -c vial/vsh/cmds/cmds.c -o build/cmds.o

	ld -m elf_i386 -T memory.ld -o build/vialos.bin \
		build/boot.o \
		build/cork.o \
		build/interrupts.o \
		build/io.o \
		build/keyboard.o \
		build/vga.o \
		build/vial.o \
		build/graphics.o \
		build/typing.o \
		build/vsh.o \
		build/cmds.o

	cp build/vialos.bin build/iso/boot/
	cp iso/boot/grub/grub.cfg build/iso/boot/grub/

	grub-mkrescue -o build/vialOSdev.iso build/iso 

clean:
	rm -rf build