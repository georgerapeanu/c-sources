#!/usr/bin/python3

import math;
import numpy as np;
import matplotlib.pyplot as plt;

f = [0,1]

def log2(x):
    return math.log(x) / math.log(2);
    

for x in range(2,400001):
    f.append(max(f[int(math.ceil(x / 2))] + (2**(math.ceil(log2(math.ceil(x / 2))))),f[int(math.floor(x / 2))] + 2 * (2**(math.ceil(log2(math.floor(x / 2)))))))

for x in range(1,400001):
    f[x] = f[x] / x;

plt.plot(f);
plt.show();

