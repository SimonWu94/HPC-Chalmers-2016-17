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

def check_time(width, height, initial, diffusion, iterations, time_bd, repeat):
  if timeit(repeat, "./heat_diffusion {} {} -i{} -d{} -n{}".format(width, height, initial, diffusion, iterations)) > time_bd:
    print( "TOO SLOW FOR {} {} -i{} -d{} -n{}".format(width, height, initial, diffusion, iterations) )

check_time( 100, 100, "1e20", "0.01", 100000, 7.26, 10 )
check_time( 10000, 10000, "1e10", "0.02", 1000, 100, 3 )
check_time( 100000, 100, "1e10", "0.6", 200, 7.0, 3 )
