assembler=as
ARM_GCC=arm-none-eabi-gcc
ARM_OBJDUMP=arm-none-eabi-objdump
ARM_OBJCOPY=arm-none-eabi-objcopy

bin: list
	$(ARM_OBJCOPY) -O binary "./build/output.elf" "./build/output.bin"

list: clean build.dir link
	$(ARM_OBJDUMP) -h -S "./build/output.elf" > "./build/output.lss"

link: test.o
	$(ARM_GCC) -o "./build/output.elf" ./build/main.o ./build/test.o -mthumb -Wl,-Map="./build/output.map" -Wl,--start-group -lm  -Wl,--end-group -L"./linker"  -Wl,--gc-sections -mcpu=cortex-m3 -Tmain.ld

main.o:
	$(ARM_GCC) -x c -mthumb -D__SAM3X8E__ -DNDEBUG -Os -ffunction-sections -mlong-calls -Wall -mcpu=cortex-m3 -c -std=gnu99 -MD -MP -MF "./build/main.d" -MT"./build/main.d" -MT"./build/main.o"  -o "./build/main.o" "./src/main.c" 

test.o: main.o 
	$(assembler) -mcpu=cortex-m3 -mthumb -o "./build/test.o" "./src/test.s"


build.dir:
	mkdir build

clean:
	rmdir /s /q build