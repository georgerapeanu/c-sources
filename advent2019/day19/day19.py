#!/usr/bin/python3

import collections;

class IntcodeComputer:
    def __init__(self,inputs,code):
        self.inputs = inputs; #list of inputs
        self.code = code; # list of code things
        self.start = 0; #last element
        self.halted = False;
        self.base = 0;
    
    def is_halted(self):
        return self.halted;
    
    def replace_inputs(self,inputs):
        self.inputs = inputs;

    def get_val(self,mode,val):
        if mode == 0:
            return int(self.code[int(val)]);
        elif mode == 1:
            return val;
        elif mode == 2:
            return int(self.code[int(self.base) + int(val)]);
        else:
            print("this is fucked2");
            return -1;

    def get_val_for_output(self,mode,val):
        if mode == 0:
            return int(val);
        elif mode == 1:
            print("this is fucked4");
            return -1;
        elif mode == 2:
            return int(self.base) + int(val);
        else:
            print("this is fucked3");
            return -1;
    
    def run(self):
        ans = []
        while self.start <= len(self.code):
            mode = int(int(self.code[self.start]) % 100);
            val = int(int(self.code[self.start]) / 100);
            self.start = int(1 + self.start);

#            print("mode is " + str(mode))
#            print("val is " + str(val))
#            print("val on start is " + str(self.code[self.start]))

            if mode == 99:
                self.halted = True;
                return ans;
            elif mode == 1:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                b = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                c = int(self.get_val_for_output(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                self.code[c] = int(a) + int(b);
            elif mode == 2:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                b = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                c = int(self.get_val_for_output(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                self.code[c] = a * b;
            elif mode == 3:
                c = int(self.get_val_for_output(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                if len(self.inputs) > 0:
                    self.code[c] = int(self.inputs[0]);self.inputs = self.inputs[1::];
                else:
                    print("please input");
                    self.code[c] = int(input());
            elif mode == 4:
                c = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                ans.append(int(c));
                if len(ans) == 1:
                    return ans[0];
            elif mode == 5:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                b = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                if a != 0:
                    self.start = b;
            elif mode == 6:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                b = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                if a == 0:
                    self.start = b;
            elif mode == 7:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                b = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                c = int(self.get_val_for_output(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                if a < b:
                    self.code[c] = 1;
                else:
                    self.code[c] = 0;
            elif mode == 8:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                b = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                c = int(self.get_val_for_output(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                if a == b:
                    self.code[c] = 1;
                else:
                    self.code[c] = 0;
            elif mode == 9:
                a = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                self.base = self.base + int(a); 
            else:
                print("this is fucked")
 
def my_process(v):
    ans = collections.defaultdict(lambda : 0)
    ans.setdefault(0)
    for x in range(0,len(v)):
        ans[int(x)] = v[x];
    return ans;

def Try(i,j,code):
    computer = IntcodeComputer([i,j],my_process(code));
    c11 = int(computer.run());
    computer = IntcodeComputer([i,j + 99],my_process(code));
    c12 = int(computer.run());
    computer = IntcodeComputer([i + 99,j + 99],my_process(code));
    c22 = int(computer.run());
    computer = IntcodeComputer([i + 99,j],my_process(code));
    c21 = int(computer.run());

    print(i,j,c11,c12,c21,c22);

    if c11 == 1 and c12 == 1 and c21 == 1 and c22 == 1:
        return True;
    return False;

def check(i,afis,code):
    for j in range(0,int(1e4 + 100)):
        print(j);
        if Try(i,j,code):
            if afis == True:
                print(i * 10000 + j);
            return True;
    return False;

def __main__():
    read_code = open("code","r");
    
    d = [(-1,0),(0,1),(1,0),(0,-1)];

    inputs = [];
    x = 0;
    y = 0;
    k = 0;
    cells = {};
    code = str(read_code.read().rstrip()).split(',');

    matrix = [];

    l = 0;
    r = int(1e4);

    while r - l > 1:
        mid = (l + r) // 2;
        print(l,r);
        if check(mid,False,code):
            r = mid;
        else:
            l = mid;

    check(r,True,code);

__main__();
