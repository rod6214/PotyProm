ARM_GCC=arm-none-eabi-gcc
ARM_OBJDUMP=arm-none-eabi-objdump
ARM_OBJCOPY=arm-none-eabi-objcopy

TARGET = template
LINKER_SCRIPT = system.ld
LINKER_FOLDER = ./linker
ASM_SRC = "./src/bios.s ./src/so.s"
INCLUDES = -I./src -I./drivers/include -I./drivers/CMSIS/include -DSTM32F103x6

CFLAGS += -mcpu=cortex-m3 -mthumb # processor setup
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

LDFLAGS += -mcpu=cortex-m3 -mthumb
LDFLAGS += -march=armv7e-m # processor setup
LDFLAGS += -nostartfiles # no start files are used
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,-Map=./build/$(TARGET).map #generate map file
LDFLAGS += -T$(LINKER_SCRIPT)
LDFLAGS += -L$(LINKER_FOLDER)
# LDFLAGS += --with-mode=thumb
LDFLAGS += -Wl,--gc-sections

build: clean build.dir main.bin

#####################################################################
main.bin: main.elf main.lss
	$(ARM_OBJCOPY) -O binary "./build/main.elf" "./build/"$@

main.lss:
	$(ARM_OBJDUMP) -h -S "./build/main.elf" > "./build/"$@

main.elf: clock.o gpio.o interrupts.o main.o startup.o target.o syscalls.o
	$(ARM_GCC) $(LDFLAGS) -o "./build/"$@ ./build/main.o ./build/interrupts.o ./build/gpio.o ./build/startup.o ./build/clock.o ./build/target.o ./build/syscalls.o

main.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/main.c

clock.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/RCC/clock.c

interrupts.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/interrupts.c

startup.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/startup.c

gpio.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/gpio.c

syscalls.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/syscalls.c

target.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/target.s


build.dir:
	mkdir build

clean:
	rmdir /s /q build