#!/usr/bin/python3

import collections;
from termcolor import colored;

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
                    self.code[c] = ord(self.inputs[0]);self.inputs = self.inputs[1::];
                else:
                    print("please input");
                    self.code[c] = int(input());
            elif mode == 4:
                c = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                ans.append(int(c));
                if len(ans) == 1:
                    return ans;
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

dx = [-1,0,1,0];
dy = [0,1,0,-1];

def __main__():
    read_code = open("code","r");

    inputs = "A,C,A,C,B,B,C,A,C,B\nL,8,R,12,R,12,R,10\nL,10,R,10,L,6\nR,10,R,12,R,10\nn\n";

    cells = collections.defaultdict(lambda : ' ');
    code = str(read_code.read().rstrip()).split(',');

    computer = IntcodeComputer(inputs,my_process(code));
   
    matrix = [];
    overlay = [];
    line = "";
    over_line = "";

    while True:
        result = computer.run();
        if computer.is_halted() == True:
            break;
        if chr(result[0]) == '\n':
            matrix.append(line);
            overlay.append(over_line);
            line = "";
            over_line = "";
        else:
            line = line + (chr(result[0]))
            over_line = over_line + (chr(result[0]));
        if result[0] < 256:
            print(chr(result[0]),end='');
        else:
            print(int(result[0]));
#    ans = 0;
#    for i in range(0,len(matrix)):
#        overlay[i] = list(matrix[i]);
#        for j in range(0,len(matrix[i])):
#            overlay[i][j] = matrix[i][j];
#            if matrix[i][j] == '#':
#                cnt = 0;
#                for k in range(0,4):
#                    if i + dx[k] >= 0 and i + dx[k] < len(matrix) and j + dy[k] >= 0 and j + dy[k] < len(matrix[i + dx[k]]) and matrix[i + dx[k]][j + dy[k]] == '#':
#                        cnt = cnt + 1;
#                if cnt > 2:
#                    overlay[i][j] = 'O';
#                    ans += i * j;
#    for i in range(0,len(overlay)):
#        overlay[i] = "".join(overlay[i]);
#        print(overlay[i]);
#
#    print(ans);
__main__();
