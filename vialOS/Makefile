all:
	mkdir -p build
	mkdir -p build/iso/boot/grub

	nasm -f elf32 boot.s -o build/boot.o

	gcc -Icork/include -m32 -ffreestanding -c cork/arch/i386/interrupts/interrupts.c -o build/interrupts.o
	gcc -Icork/include -m32 -ffreestanding -c cork/arch/i386/io/io.c -o build/io.o

	gcc -Icork/include -m32 -ffreestanding -c cork/corkmain/corkmain.c -o build/corkmain.o

	gcc -Icork/include -m32 -ffreestanding -c cork/drivers/keyboard/keyboard.c -o build/keyboard.o
	gcc -Icork/include -m32 -ffreestanding -c cork/drivers/vga/vga.c -o build/vga.o

	gcc -Icork/include -m32 -ffreestanding -c vial/libraries/graphics/graphics.c -o build/graphics.o
	gcc -Icork/include -m32 -ffreestanding -c vial/libraries/typing/typing.c -o build/typing.o

	gcc -Icork/include -m32 -ffreestanding -c vial/vialmain/vialmain.c -o build/vialmain.o

	gcc -Icork/include -m32 -ffreestanding -c vial/vsh/commands/commands.c -o build/commands.o
	gcc -Icork/include -m32 -ffreestanding -c vial/vsh/vshmain/vshmain.c -o build/vshmain.o


	ld -m elf_i386 -T memory.ld -o build/vialos.bin \
		build/boot.o \
		build/interrupts.o \
		build/io.o \
		build/corkmain.o \
		build/keyboard.o \
		build/vga.o \
		build/graphics.o \
		build/typing.o \
		build/vialmain.o \
		build/commands.o \
		build/vshmain.o

	cp build/vialos.bin build/iso/boot/
	cp iso/boot/grub/grub.cfg build/iso/boot/grub/

	grub-mkrescue -o build/vialOSdev.iso build/iso 

clean:
	rm -rf build

# TO-DO
#		.
#		├── cork
#		│   ├── arch
#		│   │   ├── i386
#	X	│   │   │   ├── interrupts
#	O	│   │   │   └── io
#		│   │   └── x86-64
#	-	│   ├── corkmain
#		│   ├── drivers
#	X	│   │   ├── keyboard
#	X	│   │   └── vga
#	O	│   └── include
#		├── iso
#		│   └── boot
#		│       └── grub
#		└── vial
#		    ├── libraries
#	X	    │   ├── graphics
#	X	    │   └── typing
#	X	    ├── vialmain
#		    └── vsh
#	X	        ├── commands
#	X	        └── vshmain