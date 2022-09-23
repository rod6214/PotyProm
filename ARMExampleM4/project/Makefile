assembler=as
ARM_GCC=arm-none-eabi-gcc
ARM_OBJDUMP=arm-none-eabi-objdump
ARM_OBJCOPY=arm-none-eabi-objcopy

bin: list
	$(ARM_OBJCOPY) -O binary "./build/output.elf" "./build/output.bin"

list: clean build.dir link
	$(ARM_OBJDUMP) -h -S "./build/output.elf" > "./build/output.lss"

link: test.o
	$(ARM_GCC) -o "./build/output.elf" ./build/test.o -mthumb -Wl,-Map="./build/output.map" -Wl,--start-group -lm  -Wl,--end-group -L"./linker"  -Wl,--gc-sections -mcpu=cortex-m4 -Tmain.ld

test.o:
	$(assembler) -mcpu=cortex-m4 -mthumb -o "./build/test.o" "./src/test.s"

build.dir:
	mkdir build

clean:
	rmdir /s /q build