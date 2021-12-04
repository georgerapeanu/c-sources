#!/usr/bin/bashrc

d1 = (4,6)
d2 = (3,9)
LIM = 10

vectors = [d1,d2,(-d1[0],-d1[1]),(-d2[0],-d2[1])]

points = {(0,0)}

while True:
  toInsert = []
  for x in points.keys():
    for d in vectors:
      if (x[0] + d[0],x[1] + d[1]) not in points:
        toInsert.append((x[0] + d[0],x[1] + d1[]))
  
  for x in toInsert:
    if abs(x[0]) <= LIM and abs(x[1]) <= LIM:
      points.append(x)
  if len(toInsert) > 0:
    break;

xs = []
ys = []
colors = []

for x in points.keys():
  xs.append(x[0]);
  ys.append(x[1]);
  color.append(1);


  
