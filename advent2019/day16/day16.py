#!/usr/bin/python3

pattern = [0,1,0,-1];

def do_convolution(a,start):
    ans = [];
    for x in range(0,len(a)):
        ans.append(0);

    for i in range(len(a) - 1,start - 1,-1):
        ans[i] = ((ans[i + 1] if i + 1 < len(a) else 0) + int(a[i])) % 10;
    return ans;

def __main__():
    a = str(input());
    n = len(a);

    b = "";

    for x in range(0,10000):
        b = b + str(a);
    start = b[0:7:];
    start = int(start);
    a = list(b);

    print(n,len(a),start);

    for x in range(0,100):
        a = do_convolution(a,start);
        print("done" + str(x));

    print(a[start:start + 8:]);

__main__();
