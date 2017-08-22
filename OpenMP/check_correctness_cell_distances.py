import argparse, os, subprocess

parser = argparse.ArgumentParser()
parser.add_argument("distreffile")
parser.add_argument("distfile")
args = parser.parse_args()

dist_ref = dict()
dist = dict()
for l in open(args.distreffile, 'r').readlines():
  l = l.split(" ")
  dist_ref[l[0].strip()] = int(l[1])

for l in open(args.distfile, 'r').readlines():
  l = l.split(" ")
  dist[l[0].strip()] = int(l[1])


error = lambda k: print( "WRONG ACCUMULATED VALUE AT {}".format(k) )
accum = 0
accum_ref = 0
for k in sorted(dist_ref.keys()):
  if k[0] == '0' and k[1] == '0':
    try:
      accum += dist[k[2:]]
    except KeyError:
      pass

  if k[0] == '0':
    try:
      accum += dist[k[1:]]
    except KeyError:
      pass

  try:
    accum += dist[k]
  except KeyError:
    pass

  try:
    accum_ref += dist_ref[k]
  except KeyError:
    pass

  if abs(accum_ref - accum) > 1000:
    error(k)

if accum != accum_ref:
  print( "WRONG TOTAL NUMBER OF VALUES" )
