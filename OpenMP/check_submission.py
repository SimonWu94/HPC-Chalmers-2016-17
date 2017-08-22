#!/usr/bin/python3

import argparse, os, subprocess, shutil


subprocess.run(["mkdir", "-p", "extracted"])
subprocess.run(["mkdir", "-p", "reports"])
subprocess.run(["mkdir", "-p", "distances"])


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
subprocess.Popen(["make", "cell_distances"], cwd=extraction_path).wait()
subprocess.Popen(["make", "clean"], cwd=extraction_path).wait()
if not all("material" in root or all(map(is_valid_file, files)) for (root, _, files) in os.walk(extraction_path)):
  print("ADDITIONAL FILES AFTER BUILD CLEAN")
  exit(1)
subprocess.Popen(["make", "cell_distances"], cwd=extraction_path, stdout=subprocess.DEVNULL).wait()

# link test data
if os.path.exists(extraction_path + "/test_data"):
  os.remove(extraction_path + "/test_data")
os.symlink(os.path.dirname(os.path.realpath(__file__)) + "/test_data", extraction_path + "/test_data")

# check times
print( "checking runtimes..." )
try:
  subprocess.Popen(
      ["python3", os.path.dirname(os.path.realpath(__file__)) + "/check_time_cell_distances.py"],
      cwd=extraction_path
      ).wait(2000)
except subprocess.TimeoutExpired:
  print("CHECK TIME DID NOT FINISH TIMELY")


# create distances
print( "checking correctness..." )
# if os.path.exists(extraction_path + "/cells"):
#   os.remove(extraction_path + "/cells")
shutil.copyfile(extraction_path + "/test_data/cell_e5", extraction_path + "/cells")
with open("distances/" + stem, 'w') as f:
  subprocess.Popen(["./cell_distances", "-t5"], cwd = extraction_path, stdout = f).wait()
subprocess.Popen(
    ["python3",
     os.path.dirname(os.path.realpath(__file__)) + "/check_correctness_cell_distances.py",
     os.path.dirname(os.path.realpath(__file__)) + "/test_data/dist_e5",
     "distances/" + stem
    ]
    ).wait(2000)

# clean
print( "final cleaning..." )
subprocess.Popen(["make", "clean"], cwd=extraction_path, stdout=subprocess.DEVNULL).wait()
