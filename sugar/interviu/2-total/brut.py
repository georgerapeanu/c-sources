f = open("in","r")
g = open("ok","w")

n = int(f.readline());
a = [int(x) for x in f.readline().split()]
p = 1

for x in a:
	p = p * x
for x in a:
	g.write(str(p // x).rstrip('\n') + " ")