#!/usr/bin/python3
#this calculates the number of operations the algo would take
#it is overestimated

v = []

for x in range(1,201):
    v.append(int(x / 2) ** 2)
    for i in range(1,int(x / 2) + 1):
        v[len(v) - 1] = v[len(v) - 1] + v[i]    
print(v[len(v) - 1])
