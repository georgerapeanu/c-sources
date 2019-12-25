#!/usr/bin/python3
import math;
import collections;

def make_comparator(less_than):
    def compare(x,y):
        print("used")
        if less_than(x,y):
            return -1;
        elif less_than(y,x):
            return 1;
        else:
            return 0;

def test_cmp(x):
    return -x

def same_dir_cmp(x):
    return x[0] * x[0] + x[1] * x[1]

def my_cmp(x):
    return (x[0],-4 if x[1] == (-1,0) else math.atan2(-x[1][1],x[1][0]));

def __main__():
    
    tmp = [1,2,3];
    tmp = sorted(tmp,key = test_cmp);
    print(tmp);

    read_input = open("in","r")

    a = []

    for line in read_input:
        a.append(line.rstrip());
    
    ans = -1;
    bst_x = 0;
    bst_y = 0;
    bst_lst = [];
    for x in range(0,len(a)):
        for y in range(0,len(a[x])):
            dic = collections.defaultdict(lambda : []);
            if a[x][y] == '#':
                for i in range(0,len(a)):
                    for j in range(0,len(a[i])):
                        if (i != x or j != y) and a[i][j] == '#':
                            dic[(int((i - x) / math.gcd(i - x,j - y)),int((j - y) / math.gcd(i - x,j - y)))].append((i - x,j - y));
            if ans < int(len(dic)):
                ans = int(len(dic))
                (bst_x,bst_y) = (x,y)
                bst_lst = []
                for xx in dic:
                    dic[xx] = sorted(dic[xx], key = same_dir_cmp);
                    for yy in range(0,len(dic[xx])):
                        bst_lst.append((yy,xx,(int(dic[xx][yy][0] + x),int(dic[xx][yy][1] + y))));
   
    bst_lst = sorted(bst_lst,key = my_cmp);

    print(ans);
    print(bst_x);
    print(bst_y);
    print(bst_lst[199]);

__main__();
