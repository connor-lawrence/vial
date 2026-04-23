all:
	mkdir -p build
	mkdir -p build/iso/boot/grub

	nasm -f elf32 boot.s -o build/boot.o

	gcc -m32 -ffreestanding -c cork/cork.c -o build/cork.o
	gcc -m32 -ffreestanding -c cork/irqs.c -o build/irqs.o
	gcc -m32 -ffreestanding -c drivers/keybd.c -o build/keybd.o
	gcc -m32 -ffreestanding -c drivers/vga.c -o build/vga.o
	gcc -m32 -ffreestanding -c vial/vial.c -o build/vial.o

	ld -m elf_i386 -T memory.ld -o build/vialos.bin \
		build/boot.o \
		build/cork.o \
		build/irqs.o \
		build/keybd.o \
		build/vga.o \
		build/vial.o

	cp build/vialos.bin build/iso/boot/
	cp iso/boot/grub/grub.cfg build/iso/boot/grub/

	grub-mkrescue -o build/VialOS0v1.iso build/iso

clean:
	rm -rf build