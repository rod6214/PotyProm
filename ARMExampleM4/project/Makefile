assembler=as
ARM_GCC=arm-none-eabi-gcc
ARM_OBJDUMP=arm-none-eabi-objdump
ARM_OBJCOPY=arm-none-eabi-objcopy

TARGET = template
LINKER_SCRIPT = main.ld
LINKER_FOLDER = ./linker

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

LDFLAGS += -march=armv7e-m # processor setup
LDFLAGS += -nostartfiles # no start files are used
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,-Map=./build/$(TARGET).map #generate map file
LDFLAGS += -T$(LINKER_SCRIPT)
LDFLAGS += -L$(LINKER_FOLDER)

bin: list
	$(ARM_OBJCOPY) -O binary "./build/output.elf" "./build/output.bin"

list: clean build.dir link
	$(ARM_OBJDUMP) -h -S "./build/output.elf" > "./build/output.lss"

link: test.o
	$(ARM_GCC) $(LDFLAGS) -o "./build/output.elf" ./build/test.o 

test.o:
	$(ARM_GCC) $(CFLAGS) -c -o "./build/test.o" "./src/test.s"

build.dir:
	mkdir build

clean:
	@rm -R build
	# rmdir /s /q build