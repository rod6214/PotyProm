ARM_GCC=arm-none-eabi-gcc
ARM_OBJDUMP=arm-none-eabi-objdump
ARM_OBJCOPY=arm-none-eabi-objcopy

TARGET = template
SO_TARGET = so_template
SO_LINKER_SCRIPT = so.ld
LINKER_SCRIPT = main.ld
LINKER_FOLDER = ./linker
ASM_SRC = "./src/bios.s ./src/so.s"
INCLUDES = -I./src/*.h

CFLAGS += -mcpu=cortex-m4 -mthumb # processor setup
CFLAGS += -O0 # optimization is off
CFLAGS += -g2 # generate debug info
CFLAGS += -fno-common
CFLAGS += -Wall # turn on warnings
CFLAGS += -pedantic # more warnings
CFLAGS += -Wsign-compare
CFLAGS += -Wcast-align
CFLAGS += -Wconversion # neg int const implicitly converted to uint
CFLAGS += -fsingle-precision-constant
CFLAGS += -fomit-frame-pointer # do not use fp if not needed
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS += -mcpu=cortex-m4 -mthumb
LDFLAGS += -march=armv7e-m # processor setup
LDFLAGS += -nostartfiles # no start files are used
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,-Map=./build/$(TARGET).map #generate map file
LDFLAGS += -T$(LINKER_SCRIPT)
LDFLAGS += -L$(LINKER_FOLDER)
# LDFLAGS += --with-mode=thumb
LDFLAGS += -Wl,--gc-sections

SO_LDFLAGS += -mcpu=cortex-m4 -mthumb
SO_LDFLAGS += -march=armv7e-m # processor setup
SO_LDFLAGS += -nostartfiles # no start files are used
SO_LDFLAGS += --specs=nosys.specs
SO_LDFLAGS += -Wl,-Map=./build/$(SO_TARGET).map #generate map file
SO_LDFLAGS += -T$(SO_LINKER_SCRIPT)
SO_LDFLAGS += -L$(LINKER_FOLDER)
# SO_LDFLAGS += --with-mode=thumb
SO_LDFLAGS += -Wl,--gc-sections

build: clean build.dir bios.bin main.bin

main.bin: main.elf main.lss
	$(ARM_OBJCOPY) -O binary "./build/main.elf" "./build/"$@

bios.bin: bios.elf bios.lss
	$(ARM_OBJCOPY) -O binary "./build/bios.elf" "./build/"$@

bios.lss:
	$(ARM_OBJDUMP) -h -S "./build/bios.elf" > "./build/"$@

main.lss:
	$(ARM_OBJDUMP) -h -S "./build/main.elf" > "./build/"$@

main.elf: gpio.o interrupts.o main.o startup.o
	$(ARM_GCC) $(SO_LDFLAGS) -o "./build/"$@ ./build/main.o ./build/interrupts.o ./build/gpio.o ./build/startup.o

bios.elf: bios.o
	$(ARM_GCC) $(LDFLAGS) -o "./build/"$@ ./build/bios.o

main.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/main.c

bios.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/bios.s

# so.o:
# 	$(ARM_GCC) $(CFLAGS) -c -o "./build/"$@ ./src/so.s

interrupts.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/interrupts.c

startup.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/startup.c

gpio.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/gpio.c

build.dir:
	mkdir build

clean:
	rmdir /s /q build