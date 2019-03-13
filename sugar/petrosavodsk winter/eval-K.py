import subprocess

for x in range(1,90):
    a = str(x);
    while len(a) < 3:
        a = "0" + a;
    subprocess.call("cp " + a + " in",shell=True)
    subprocess.call("cp " + a + ".a ok",shell=True)
    subprocess.call("time ./K.exe",shell=True)
    subprocess.call("./check-K.exe",shell=True)
