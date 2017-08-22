import os
from time import perf_counter
import subprocess


def timeit(repeat, cmd):
  times = []
  for _ in range(repeat):
    t = perf_counter()
    subprocess.Popen(cmd, shell = True, stdout = subprocess.DEVNULL).wait()
    times.append(perf_counter() - t)
  return min(times)

def check_time(nmb_process, src, dest, graph, time_bd, repeat):
  if timeit(repeat, "mpirun -n {} ./dijkstra {} {} {}".format(nmb_process, src, dest, graph)) > time_bd:
    print( "TOO SLOW FOR mpirun -n {} ./dijkstra {} {} {}".format(nmb_process, src, dest, graph) )

check_time( 1, 9, 82,   "/home/hpc01/a5_grading/test_data/graph_de1_ne3_we2", 0.26, 10 )
check_time( 1, 17, 40,  "/home/hpc01/a5_grading/test_data/graph_de2_ne4_we2", 9.92, 5 )
check_time( 4, 17, 18,  "/home/hpc01/a5_grading/test_data/graph_de2_ne4_we2", 2.64, 10 )
check_time( 10, 107, 0, "/home/hpc01/a5_grading/test_data/graph_de2_ne5_we2", 97, 2 )
check_time( 20, 4, 5,   "/home/hpc01/a5_grading/test_data/graph_de3_ne5_we3", 472, 2 )
