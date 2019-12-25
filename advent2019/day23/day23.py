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
        self.ans = [];
    
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
                if len(self.inputs) == 0:
                    self.inputs = [-1];
                self.code[c] = int(self.inputs[0]);self.inputs = self.inputs[1::];
            elif mode == 4:
                c = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                self.ans.append(int(c));
                if len(self.ans) == 3:
                    tmp = list(self.ans);
                    self.ans = [];
                    return tmp;
                    
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

    def run_one_step(self):
        if self.start <= len(self.code):
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
                if len(self.inputs) == 0:
                    self.inputs = [-1];
                self.code[c] = int(self.inputs[0]);self.inputs = self.inputs[1::];
            elif mode == 4:
                c = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                self.ans.append(int(c));
                if len(self.ans) == 3:
                    tmp = self.ans;
                    self.ans = [];
                    return tmp;
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
        return [];
 
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

    cells = collections.defaultdict(lambda : ' ');
    code = str(read_code.read().rstrip()).split(',');

    computers = [];
    
    for x in range(0,50):
        computers.append(IntcodeComputer([x],my_process(code)));

    last_packet_sent = 0;
    pack = [];
    lst_sent = -123;

    while True:
        tmp = [];

        for x in range(0,50):
            tmp.append(computers[x].run_one_step());
        for x in tmp:
            if len(x) == 0:
                continue;
            last_packet_sent = 0;
            if x[0] == 255:
                pack = x;
            else:
                computers[x[0]].inputs.append(x[1]);
                computers[x[0]].inputs.append(x[2]);

        last_packet_sent += 1;

        print(pack);

        if last_packet_sent > 1000:
            computers[0].inputs.append(pack[1]);
            if lst_sent == pack[2]:
                print(lst_sent);
                return ;
            computers[0].inputs.append(pack[2]);
            lst_sent = pack[2];
            pack = [];
            last_packet_sent = 0;

__main__();

