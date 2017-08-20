CC=gcc -std=c99
CFLAGS = -I.
ASSEMBLY = -S 

.PHONY: all clean assembler

all: main0 main1 main2 main3 mains maing

main0 main1 main2 main3 mains maing: main%: indirect_addressing.c
	$(CC) $(CFLAGS) -O$* indirect_addressing.c -o main$*.out 

clean: 
	-rm -f  *.o *.out *.s
	@echo Finished Cleaning!
