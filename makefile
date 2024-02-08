CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
INCS= -I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
project_name =Islam_Cortex_M3

all: $(project_name).bin
	@echo "Build is done"
%.o: %.c
	$(CC)gcc.exe -c  $(INCS) $(CFLAGS) $< -o $@
	
$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld  $(LIBS) $(ASOBJ) $(OBJ) -o $@ -Map=Map_file.map
	

	
$(project_name).bin: $(project_name).elf
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
	rm *.o *.elf *.bin *.map

clean:
	rm *.elf *.bin *.map