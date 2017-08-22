#!/usr/bin/python3

import os
from time import perf_counter
import subprocess

print("Checking runtimes....")

def timeit(repeat, cmd):
  times = []
  for _ in range(repeat):
    t = perf_counter()
    subprocess.Popen(cmd, shell = True, stdout = subprocess.DEVNULL).wait()
    times.append(perf_counter() - t)
  return sum(times)/len(times)

def check_time(width,height,initValue, diffConst, nIt, repeat):
  time = timeit(repeat, "./heat_diffusion {} {} -i{} -d{} -n{}".format(width, height, initValue, diffConst, nIt))
  print( "AVERAGE FOR ./heat_diffusion {} {} -i{} -d{} -n{} is {}".format(width, height, initValue, diffConst, nIt, time ))

check_time( 100, 100,1e20,0.01,100000, 10 )
check_time( 10000, 10000,1e10,0.02,1000, 10 )
check_time( 100000, 100,1e10,0.6,200, 50 )
