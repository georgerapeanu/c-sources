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
        self.px = 0;
        self.py = 0;
        self.dx = 0;
        self.dy = 0;
        self.cells = {};
        self.cells[(0,0)] = '.';
        self.upleft = (0,0);
        self.downright = (0,0);

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

    def print_state(self):
        for x in range(self.upleft[0],self.downright[0] + 1):
            for y in range(self.upleft[1],self.downright[1] + 1):
                print(('O' if (x,y) == (self.px,self.py) and self.cells[(x,y)] != 'X' else self.cells[(x,y)]) if (x,y) in self.cells else " ",end = ' ');
            print();
    
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
                tmp = "";
                if len(self.inputs) > 0:
                    tmp = [self.inputs[0]];
                    self.inputs.pop(0);
                else: 
                    tmp = str(input()).rstrip();
                
                if tmp[0] == "a":
                    self.code[c] = 3;
                    self.dx = 0;
                    self.dy = -1;
                elif tmp[0] == "d":
                    self.code[c] = 4;
                    self.dx = 0;
                    self.dy = 1;
                elif tmp[0] == "w":
                    self.code[c] = 1;
                    self.dx = -1;
                    self.dy = 0;
                else:
                    self.code[c] = 2;
                    self.dx = 1;
                    self.dy = 0;
            elif mode == 4:
                c = int(self.get_val(int(val % 10),self.code[self.start]));self.start = 1 + self.start;val = int(val / 10);
                ans = [int(c)];
                int(ans[0]);
                ok = False;
                if ans[0] == 0:
                    self.cells[(self.px + self.dx,self.py + self.dy)] = '#';
                    self.upleft = (min(self.upleft[0],self.px + self.dx),min(self.upleft[1],self.py + self.dy));
                    self.downright = (max(self.downright[0],self.px + self.dx),max(self.downright[1],self.py + self.dy));
                    ok = False;
                else:
                    self.upleft = (min(self.upleft[0],self.px + self.dx),min(self.upleft[1],self.py + self.dy));
                    self.downright = (max(self.downright[0],self.px + self.dx),max(self.downright[1],self.py + self.dy));
                    self.px = self.px + self.dx;
                    self.py = self.py + self.dy;
                    self.cells[(self.px,self.py)] = ('X' if ans[0] == 2 else '.');
                    ok = True;
                self.print_state();
                return ok;
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
move = ["w","d","s","a"]
move_back = ["s","a","w","d"];

def dfs(x,y,computer):
    for k in range(0,4):
        if (x + dx[k],y + dy[k]) in computer.cells:
            continue;
        computer.replace_inputs([move[k]]);
        ans = computer.run();
        if ans == True:
            dfs(x + dx[k],y + dy[k],computer);
            computer.replace_inputs([move_back[k]]);
            computer.run();

def bfs(x,y,computer):
    q = [(x,y)];
    dist = {(x,y):0};
    lst_dist = 0;
    while len(q) > 0:
        cell = q[0];q.pop(0);
        lst_dist = dist[cell];
        for k in range(0,4):
            if ((cell[0] + dx[k],cell[1] + dy[k]) not in dist) and ((cell[0] + dx[k],cell[1] + dy[k]) in computer.cells) and (computer.cells[(cell[0] + dx[k],cell[1] + dy[k])] != '#'):
                dist[(cell[0] + dx[k],cell[1] + dy[k])] = 1 + dist[cell];
                q.append((cell[0] + dx[k],cell[1] + dy[k]));
    return lst_dist;

def __main__():
    read_code = open("code","r");
    
    inputs = [];
    code = str(read_code.read().rstrip()).split(',');

    computer = IntcodeComputer(inputs,my_process(code));

    dfs(0,0,computer);
    coord = (0,0);
    for x in computer.cells:
        if computer.cells[x] == 'X':
            coord = x;
            break;
    print(bfs(coord[0],coord[1],computer));
__main__();
