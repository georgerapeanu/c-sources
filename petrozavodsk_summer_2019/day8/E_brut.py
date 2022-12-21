
def eval(num, k):
  if num == 0:
    return 0
  digits = []
  while num > 0:
    digits.append(num % k)
    num = num // k
  return len(digits) + sum(digits) - 2


t = int(input())

for test in range(1, t + 1):
  _i = input().strip().split(" ")
  k = int(_i[0])
  l = int(_i[1])
  r = int(_i[2])

  best = (0, l, l)

  for i in range(l, r + 1):
    if eval(i, k) > best[0]:
      best = (eval(i, k), i, i)
    elif eval(i, k) == best[0]:
      best = (best[0], best[1], i)
  print("Case #%d: %d %d %d" % (test, best[0], best[1], best[2]))



