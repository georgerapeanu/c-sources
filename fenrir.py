import itertools as i;a=range(1,20);f=open("fenrir.out","a");f.write("99\n")
for x in i.product([*a[::2]]+[20],a[1::2]):
	f.write("%d %d\n" %x)