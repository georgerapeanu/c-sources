import sys

def get_string(l,a):
	expected = 1;

	s = "";

	for i in range(l,-1,-1):
		if ((a >> i) & 1) == expected:
			s = s + "0";
			expected = 1 - expected;
		else:
			s = s + "10";

	return s;

def __main__():

	mods = [998244353]

	a = 1;
	
	for x in mods:
		a = a * x;

	a = a + 1;
	b = 1;

	l = 100;
	
	while(a >> l) == 0:
		l = l - 1;
	s = get_string(l,a);
	t = get_string(l,b);

	while(len(s) < len(t)):
		s = s + "1";
	while(len(t) < len(s)):
		t = t + '1';

	print(len(t) + len(s))
	print(s + t)
	print(1);
	print("1 " + str(int(len(s) + 1)) + " " + str(int(len(s))))
	sys.stdout.flush()

__main__();