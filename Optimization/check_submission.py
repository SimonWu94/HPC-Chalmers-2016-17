#!/usr/bin/python3

import argparse, os, subprocess


subprocess.run(["mkdir", "-p", "extracted"])
subprocess.run(["mkdir", "-p", "reports"])


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

# # check files
# is_valid_file = lambda f: ( 
#      f in ["makefile", "Makefile"] or
#      f.endswith(".sh") or
#      f == "report.markdown" or
#      f.endswith(".cc") or f.endswith(".c") or
#      f.endswith(".hh") or f.endswith(".h") )
# 
# print( "checking for additional files..." )
# if not all(map(is_valid_file, os.listdir(extraction_path))):
#   print("ADDITIONAL FILES IN TAR ROOT")
# 
# # build clean build
# for (task,prog) in [("time","time"),
#                     ("inlining","inlining"),
#                     ("locality","locality"),
#                     ("indirect_addressing","indirect_addressing"),
#                     ("valgrind","leak")]:
#   print( "bulding and cleaning " + task + "..." )
#   extraction_path_task = extraction_path + "/" + task
#   subprocess.Popen(["make", prog], cwd=extraction_path_task).wait()
#   subprocess.Popen(["make", "clean"], cwd=extraction_path_task).wait()
#   if not all(map(is_valid_file, os.listdir(extraction_path_task))):
#     print("ADDITIONAL FILES AFTER BUILD CLEAN " + task)
#   subprocess.Popen(["make", prog], cwd=extraction_path_task, stdout=subprocess.DEVNULL).wait()
# 
# subprocess.Popen(["make", "time"], cwd=extraction_path + "/time").wait()
# subprocess.Popen(["make", "check"], cwd=extraction_path + "/valgrind").wait()
