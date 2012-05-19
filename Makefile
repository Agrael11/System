CFLAGS = -c \
-Wall \
-Wextra \
-nostdlib \
-fno-builtin \
-nostartfiles \
-nodefaultlibs \
-fno-exceptions \
-fno-rtti \
-fno-stack-protector \
-std=c++0x \
-ffreestanding \
-mno-mmx \
-mno-sse \
-mno-sse2 \
-mno-sse3 \
-mno-3dnow \
-mno-red-zone \
-I ./include \
-O2 \
-m32 \

#-mcmodel=kernel \

SRCx += $(wildcard kernel/*.asm kernel/*.cpp)
SRCx += $(wildcard init/*.cpp)
OBJSx = $(SRC:.cpp=.o)
OBJS = $(OBJSx:.asm=.a.o)


SRCb += $(wildcard bootloader/loader/*.asm bootloader/loader/*.cpp)
OBJSbx = $(SRCb:.cpp=.o)
OBJSb = $(OBJSbx:.asm=.a.o)



kernel: clean $(OBJS)
	@ld -T link.ld -o build/kernel.bin $(OBJS) -Map build/os.map
	@echo "OS is builded successful!"

%.o: %.cpp
	@echo "[GCC]     " $@
	@g++ $(CFLAGS) $^ -o $@

%.a.o: %.asm
	@echo "[NASM]    " $@
	@nasm $^ -f elf32 -o $@
	

boot: $(OBJSb)
	@echo "[NASM]    Bootlaoder"
	@ld -T bootloader/loader/link.ld -o build/loader.bin $(OBJSb) -Map build/loader.map -melf_i386
	@nasm -f bin bootloader/bootloader.asm -o build/bootloader.bin

clean:
	@-rm -rf $(OBJS)
	@-rm -rf $(OBJSb)
	@-rm -rf build/kernel.bin
	@-rm -rf build/loader.bin
	@-rm -rf build/bootloader.bin
	@echo "Cleaned"
	
debug: boot
	@-rm -rf build/boot.img

	@cat build/bootloader.bin > build/boot.img
	@cat build/loader.bin >> build/boot.img
	@cat build/null >> build/boot.img
	@qemu -fda build/boot.img -boot a -m 256 -monitor stdio -no-kvm -vga std
