SHELL = /bin/bash
CC =gcc
CFLAGS =-O2 -march=native 
OpenCL =-I/usr/local/cuda-7.5/targets/x86_64-linux/include -L/usr/local/cuda-7.5/targets/x86_64-linux/lib -lOpenCL
DEBUGGER = -Wall
OpenCLapple = -framework OpenCL

.PHONY: all time clean debugg test zip gprof

all: heat_diffusion

heat_diffusion: heat_diffusion.c
	$(CC) $(CLAGS) heat_diffusion.c $(OpenCL) -lm -o heat_diffusion
gprof:
	$(CC) $(CLAGS) heat_diffusion.c $(OpenCL) -lm -pg -o heat_diffusion

clean: 
	rm -f heat_diffusion 
	echo "finished cleaning"

time:		
	python3 ./timer.py heat_heat_diffusion

debugg:
	$(CC) $(CLAGS) $(DEBUGGER) heat_diffusion.c $(OpenCL) -lm -g

test:
	time ./heat_diffusion 100 100 -i1e20 -d0.01 -n100000
	time /home/hpc01/a4_grading/example/heat_diffusion 100 100 -i1e20 -d0.01 -n100000
	time ./heat_diffusion 10000 10000 -i1e10 -d0.02 -n1000
	time /home/hpc01/a4_grading/example/heat_diffusion 10000 10000 -i1e10 -d0.02 -n1000
	time ./heat_diffusion 100000 100 -i1e10 -d0.6 -n200
	time /home/hpc01/a4_grading/example/heat_diffusion 100000 100 -i1e10 -d0.6 -n200

alt:
	./heat_diffusion 3 3 -i1e6 -d0.033333 -n2
	./heat_diffusion 3 3 -i1e6 -d0.033333 -n4
zip:
	tar czvf gast_lamy_moenne-loccoz.tar.gz Makefile heat_diffusion.c kernels.cl report.markdown
mv:	
	mv ./gast_lamy_moenne-loccoz.tar.gz ./test/.

