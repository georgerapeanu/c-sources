#!/bin/python3

import random

# [N, count]
SUBTASKS = [
  [8, 2],
  [8, 5],
  [100, 5],
  [5000, 10]
]


if __name__ == "__main__":
  for i in range(0, len(SUBTASKS)):
    subtask = SUBTASKS[i]
    for j in range(0, subtask[1]):
      with open("test_%d_%d.in" % (i, j), "w") as f:
        n = subtask[0]
        perm = [x for x in range(1, n + 1)]
        random.shuffle(perm)
        g = n

        for x in range(10):
          g = min(g, random.randint(1, n)) #to bias it to be less


        lengths = [x for x in range(1, n + 1) if x % g == 0]
        
        random.shuffle(lengths)
        k = random.randint(1, len(lengths))
        lengths = lengths[0:k]
        
        f.write("%d %d\n" % (n, k));
        
        for x in range(0, len(perm)):
          f.write("%d" % perm[x])
          if x + 1 < len(perm):
            f.write(" ")
        f.write("\n")

        for x in range(0, len(lengths)):
          f.write("%d" % lengths[x])
          if x + 1 < len(lengths):
            f.write(" ")
        f.write("\n")
