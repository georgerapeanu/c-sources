#!/usr/bin/python

def my_pow(b,e,mod):
    p = 1;
    while e > 0:
        if e % 2 == 1:
            p = (p * b) % mod;
        b = (b * b) % mod;
        e = e // 2;
    return p;

def __main__():

    f = open("in","r");

#   polynomial style
    a1 = 1;
    a0 = 0;

    for line in f:
        tmp = (line.rstrip()).split(' ');
        if len(tmp) == 2:
            a0 -= int(tmp[1]);
        elif tmp[2] == "new":
            a1 *= -1;
            a0 *= -1;
            a0 -= 1;
        else:
            a1 *= int(tmp[3]);
            a0 *= int(tmp[3]);
    n = 119315717514047;
    cnt_iter = 101741582076661;
    x = 2020;
#    n = 10007;
#    cnt_iter = 1;
#    x = 2019;

    #a1 ^ iter * x + a1 ^ (iter - 1) * a0 + a1 ^ (iter - 2) * a0 + ... + a1 ^ 0 * a0
    #a0 * (a1 ^ iter - 1) / (a1 - 1) + a1 ^ iter * x

# this is to find the position x ends on
#    pos = (my_pow(a1,cnt_iter,n) * x + a0 * (my_pow(a1,cnt_iter,n) - 1) * my_pow(a1 - 1,n - 2,n)) % n;

# this is to find the element on position x
    pos = ((x - a0 * (my_pow(a1,cnt_iter,n) - 1) * my_pow(a1 - 1,n - 2,n)) * my_pow(my_pow(a1,cnt_iter,n),n - 2,n)) % n
    

    if pos < 0:
        pos += n;

    print(pos);

__main__();
