ARM_GCC=arm-none-eabi-gcc
ARM_OBJDUMP=arm-none-eabi-objdump
ARM_OBJCOPY=arm-none-eabi-objcopy

TARGET = template
SO_TARGET = so_template
SO_LINKER_SCRIPT = so.ld
LINKER_SCRIPT = bios.ld
LINKER_FOLDER = ./linker
ASM_SRC = "./src/bios.s ./src/so.s"
INCLUDES = -I./src/*.h

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

SO_LDFLAGS += -mcpu=cortex-m3 -mthumb
SO_LDFLAGS += -march=armv7e-m # processor setup
SO_LDFLAGS += -nostartfiles # no start files are used
SO_LDFLAGS += --specs=nosys.specs
SO_LDFLAGS += -Wl,-Map=./build/$(SO_TARGET).map #generate map file
SO_LDFLAGS += -T$(SO_LINKER_SCRIPT)
SO_LDFLAGS += -L$(LINKER_FOLDER)
# SO_LDFLAGS += --with-mode=thumb
SO_LDFLAGS += -Wl,--gc-sections

build: clean build.dir main.bin ops.bin

#####################################################################
main.bin: main.elf main.lss
	$(ARM_OBJCOPY) -O binary "./build/main.elf" "./build/"$@

main.lss:
	$(ARM_OBJDUMP) -h -S "./build/main.elf" > "./build/"$@

main.elf: clock.o gpio.o interrupts.o main.o startup.o fmc.o target.o
	$(ARM_GCC) $(LDFLAGS) -o "./build/"$@ ./build/main.o ./build/interrupts.o ./build/gpio.o ./build/startup.o ./build/clock.o ./build/fmc.o ./build/target.o

main.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/main.c

fmc.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/fmc.c

clock.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/clock.c

interrupts.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/interrupts.c

startup.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/startup.c

gpio.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/gpio.c

target.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/target.s

#########################################################################
ops.bin: ops.elf ops.lss
	$(ARM_OBJCOPY) -O binary "./build/ops.elf" "./build/"$@

ops.lss:
	$(ARM_OBJDUMP) -h -S "./build/ops.elf" > "./build/"$@

ops.elf: ops.o
	$(ARM_GCC) $(SO_LDFLAGS) -o "./build/"$@ ./build/ops.o ./build/startup.o ./build/interrupts.o

ops.o:
	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/system/main.c

# ointerrupts.o:
# 	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/system/ointerrupts.c

# ostartup.o:
# 	$(ARM_GCC) $(CFLAGS) $(INCLUDES) -c -o "./build/"$@ ./src/system/ostartup.c

build.dir:
	mkdir build

clean:
	rmdir /s /q build