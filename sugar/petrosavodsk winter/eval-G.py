import subprocess

for x in range(1,88):
    a = str(x);
    while len(a) < 3:
        a = "0" + a;
    subprocess.call("./G.exe<" + a + ">" + a + ".me",shell=True)
    f1 = open(a + ".a","r")
    f2 = open(a + ".me","r");
    b = str(f1.readline())
    c = str(f2.readline())

    if b == c:
        print("OK\n")
    else:
        print("WA on test " + a + "\n")

