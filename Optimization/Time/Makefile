CC=gcc -std=c99
CFLAGS = -I.
ASSEMBLY = -S 

.PHONY: all clean time assembler

all: main0 main1 main2 main3 mains maing

main0 main1 main2 main3 mains maing: main%: main.c
	$(CC) $(CFLAGS) -O$* main.c -o main$*.out 

time: 
	time -p bash -c "for i in {1..100}; do ./main0.out ; done " 
	time -p bash -c "for i in {1..100}; do ./main1.out ; done "
	time -p bash -c "for i in {1..100}; do ./main2.out ; done "
	time -p bash -c "for i in {1..100}; do ./main3.out ; done "
	time -p bash -c "for i in {1..100}; do ./mains.out ; done "
	time -p bash -c "for i in {1..100}; do ./maing.out ; done "	

assembler:
	$(CC) $(ASSEMBLY) $(CFLAGS) -O0 main.c -o main0.s
	$(CC) $(ASSEMBLY) $(CFLAGS) -O1 main.c -o main1.s 
	$(CC) $(ASSEMBLY) $(CFLAGS) -O2 main.c -o main2.s 
	$(CC) $(ASSEMBLY) $(CFLAGS) -O3 main.c -o main3.s 
	$(CC) $(ASSEMBLY) $(CFLAGS) -Os main.c -o mains.s   
	$(CC) $(ASSEMBLY) $(CFLAGS) -Og main.c -o maing.s 
clean: 
	-rm -f  *.o *.out *.s
	@echo Finished Cleaning!
