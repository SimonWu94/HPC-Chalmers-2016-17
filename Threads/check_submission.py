#!/usr/bin/python3

import argparse, os, subprocess


subprocess.run(["mkdir", "-p", "extracted"])
subprocess.run(["mkdir", "-p", "reports"])
subprocess.run(["mkdir", "-p", "pictures"])


parser = argparse.ArgumentParser()
parser.add_argument("tarfile")
args = parser.parse_args()

tar_file = args.tarfile
assert( tar_file.endswith(".tar.gz") )

stem = tar_file[:-7]
while stem.find("/") != -1:
  stem = stem[stem.find("/")+1:]

extraction_path = "extracted/" + stem


# extract
print( "extracting..." )
subprocess.run(["mkdir", extraction_path])
subprocess.run(["tar", "xf", tar_file, "-C", extraction_path])

# build report
print( "building report..." )
subprocess.run(["pandoc", "-o", "reports/" + stem + ".html", extraction_path + "/report.markdown"])

# check files
is_valid_file = lambda f: ( 
     f in ["makefile", "Makefile"] or
     f == "report.markdown" or
     f.endswith(".cc") or f.endswith(".c") or
     f.endswith(".hh") or f.endswith(".h") )

print( "checking for additional files..." )
if not all("material" in root or all(map(is_valid_file, files)) for (root, _, files) in os.walk(extraction_path)):
  print("ADDITIONAL FILES IN TAR")
  exit(1)

# build clean build
print( "bulding and cleaning..." )
subprocess.Popen(["make", "newton"], cwd=extraction_path).wait()
subprocess.Popen(["make", "clean"], cwd=extraction_path).wait()
if not all("material" in root or all(map(is_valid_file, files)) for (root, _, files) in os.walk(extraction_path)):
  print("ADDITIONAL FILES AFTER BUILD CLEAN")
  exit(1)
subprocess.Popen(["make", "newton"], cwd=extraction_path, stdout=subprocess.DEVNULL).wait()

# check times
print( "checking runtimes..." )
try:
  subprocess.Popen(
      ["python3", os.path.dirname(os.path.realpath(__file__)) + "/check_time_newton.py"],
      cwd=extraction_path
      ).wait(2000)
except subprocess.TimeoutExpired:
  print("CHECK TIME DID NOT FINISH TIMELY")

# copy pictures
print( "creating test picture..." )
subprocess.run([extraction_path + "/newton", "-l1000", "-t4", "7"])
subprocess.run(["mv", "newton_attractors_x7.ppm", "pictures/" + stem + "_attractors.ppm"])
subprocess.run(["mv", "newton_convergence_x7.ppm", "pictures/" + stem + "_convergence.ppm"])

# clean
print( "final cleaning..." )
subprocess.Popen(["make", "clean"], cwd=extraction_path, stdout=subprocess.DEVNULL).wait()
