XMAX = 1000
KMAX = 100
TMAX = 10

import random

t = random.randint(1, TMAX)

print(t)

for i in range(t):
  l = random.randint(1, XMAX)
  r = random.randint(l, XMAX)
  k = random.randint(2, KMAX)
  print("%d %d %d" % (k, l, r))
