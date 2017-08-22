from time import perf_counter
import subprocess


def call_newton(l, t, d):
  subprocess.run([
      "./newton",
      "-l{}".format(l), "-t{}".format(t),
      "{}".format(d)
      ])

def timeit(f, *args, repeat):
  times = []
  for _ in range(repeat):
    t = perf_counter()
    f(*args)
    times.append(perf_counter() - t)
  return min(times)

def check_time_newton(l, t, d,  time_bd, repeat=10):
  if timeit(call_newton, l, t, d, repeat=repeat) > time_bd:
    print( "TOO SLOW FOR -l{} -t{} -d{}"
           .format(l,t,d) )
  
check_time_newton(1000, 1, 1,  0.246,  100)
check_time_newton(1000, 1, 2,  0.292,  100)
check_time_newton(1000, 1, 4,  3.876)
check_time_newton(1000, 1, 7,  5.600)

check_time_newton(1000, 1, 5,  3.876)
check_time_newton(1000, 2, 5,  2.058)
check_time_newton(1000, 3, 5,  1.488)
check_time_newton(1000, 4, 5,  1.176)

check_time_newton(1000, 10, 7,  0.798)
check_time_newton(50000, 10, 7,  1055, 1)
