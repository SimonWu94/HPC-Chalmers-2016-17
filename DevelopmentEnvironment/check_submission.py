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

# check files
is_valid_file = lambda f: ( 
     f == "report.markdown"
     )

print( "checking for additional files..." )
if not all(map(is_valid_file, os.listdir(extraction_path))):
  print("ADDITIONAL FILES IN TAR")
