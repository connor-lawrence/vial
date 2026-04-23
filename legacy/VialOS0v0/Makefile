BUILD = build

all:
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/iso/boot/grub

	nasm -f elf32 boot.s -o $(BUILD)/boot.o

	gcc -m32 -ffreestanding -c cork/cork.c -o $(BUILD)/cork.o
	gcc -m32 -ffreestanding -c vial/vial.c -o $(BUILD)/vial.o

	ld -m elf_i386 -T memory.ld -o $(BUILD)/vialos.bin \
		$(BUILD)/boot.o \
		$(BUILD)/cork.o \
		$(BUILD)/vial.o

	cp $(BUILD)/vialos.bin $(BUILD)/iso/boot/
	cp iso/boot/grub/grub.cfg $(BUILD)/iso/boot/grub/

	grub-mkrescue -o $(BUILD)/VialOS0v0.iso $(BUILD)/iso

clean:
	rm -rf $(BUILD)