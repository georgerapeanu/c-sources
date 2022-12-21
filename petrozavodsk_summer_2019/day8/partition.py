from itertools import permutations
from copy import deepcopy

def partition(a):
  i = 0
  j = len(a) - 1
  m = (i + j) // 2
  pivot = a[m]
  a[m] = a[i]
  while i < j:
    while i < j and a[j] >= pivot:
      j = j - 1
    if i < j:
      a[i] = a[j]
    while i < j and a[i] < pivot:
      i  = i + 1
    if i < j:
      a[j] = a[i];
  a[i] = pivot
  return i, a


l = list(permutations(range(1, 6)))
for elem in l:
  print(list(elem), "->", partition(deepcopy(list(elem))))
