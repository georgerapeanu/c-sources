#!/usr/bin/python3

import random

rng = random.Random(2003)

command_fmt = "gen -n %d -m %d > $"

prime_numbers = [23] * 1 + [71] * 1 + [53] * 1 + [1000000007] * 5 + [666013] * 5 + [998244353] * 5 + [997] * 2

tests = [
  (11, 5),
  (20, 5),
  (50, 10),
  (100, 20),
  (500, 25)
]

used = {None:1}

for subtask in tests:
  for test in range(subtask[1]):
    script = None
    while script in used:
      script = (command_fmt % (rng.randint(1, subtask[0]), rng.choice(prime_numbers)))
    used[script] = 1  
    print(script)
    
