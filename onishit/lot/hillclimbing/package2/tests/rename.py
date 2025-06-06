#!/usr/bin/python3

import subprocess

def pad(i, k):
  ans = str(i)
  while len(ans) < k:
    ans = "0" + ans
  return ans

last_test = 0

def move_tests_to_subtask(t, task):
  global last_test
  for i in range(0, t):
    last_test += 1
    subprocess.call("mv %s subtask_%d_%d.in" % (pad(last_test, 2), task, i + 1), shell=True)
    subprocess.call("mv %s.a subtask_%d_%d.ok" % (pad(last_test, 2), task, i + 1), shell=True)

move_tests_to_subtask(3, 1)
move_tests_to_subtask(9, 2)
move_tests_to_subtask(12, 3 )
move_tests_to_subtask(3, 4)
move_tests_to_subtask(32, 5)
move_tests_to_subtask(15, 6)

