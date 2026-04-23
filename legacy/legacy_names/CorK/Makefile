BUILD = build

all:
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/iso/boot/grub

	nasm -f elf32 source/boot.asm -o $(BUILD)/boot.o
	gcc -m32 -ffreestanding -c source/kernel.c -o $(BUILD)/kernel.o

	ld -m elf_i386 -T memory.ld -o $(BUILD)/cork.bin $(BUILD)/boot.o $(BUILD)/kernel.o

	cp $(BUILD)/cork.bin $(BUILD)/iso/boot/
	cp iso/boot/grub/grub.cfg $(BUILD)/iso/boot/grub/

	grub-mkrescue -o $(BUILD)/cork.iso $(BUILD)/iso

clean:
	rm -rf $(BUILD)