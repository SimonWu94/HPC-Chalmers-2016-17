import os, shutil
from time import perf_counter
import subprocess


def timeit(repeat, cmd):
  times = []
  for _ in range(repeat):
    t = perf_counter()
    subprocess.Popen(cmd, shell = True, stdout = subprocess.DEVNULL).wait()
    times.append(perf_counter() - t)
  return min(times)

def check_time(t, s, time_bd, repeat):
#  if os.path.exists("./cells"):
#    os.remove("./cells")
  shutil.copyfile("./test_data/cell_e{}".format(s), "./cells")
  if timeit(repeat, "./cell_distances -t{} ".format(t)) > time_bd:
    print( "TOO SLOW FOR -t{} cell_e{}".format(t,s) )
  
check_time( 1, 4, 0.54, 10)
check_time( 5, 5, 13.4,  5)
check_time(10, 5, 6.62, 10)
check_time(20, 5, 3.98, 10)
