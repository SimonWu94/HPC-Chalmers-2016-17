CC=gcc -std=c99
CFLAGS = -I.
ASSEMBLY = -S 

.PHONY: all clean 

all: main0 main1 main2 main3 mains maing

main0 main1 main2 main3 mains maing: main%: locality.c
	$(CC) $(CFLAGS) -O$* locality.c -o main$*.out 

clean: 
	-rm -f  *.o *.out *.s
	@echo Finished Cleaning!
