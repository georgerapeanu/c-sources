#!/usr/bin/python3
import struct;
import numpy;

def d(p1,p2):
    if p1 < p2:
        return 1;
    elif p1 == p2:
        return 0;
    else:
        return -1;

def recalc(p1,p2,v1,v2):
    return ((v1[0] + d(p1[0],p2[0]),v1[1] + d(p1[1],p2[1]),v1[2] + d(p1[2],p2[2])),(v2[0] - d(p1[0],p2[0]),v2[1] - d(p1[1],p2[1]),v2[2] - d(p1[2],p2[2])))

def __main__():
    
    f = open("in","r");

    pos = [];
    vel = [];

    for line in f:
        (x,y,z) = line.rstrip().split(' ');
        pos.append([int(x),int(y),int(z)]);
        vel.append([0,0,0]);

    stuff = [];

    for coord in range(0,3):
        _dict = {}
        t = 0;
        coord_pos = [i[coord] for i in pos];
        coord_vel = [i[coord] for i in vel];
        while True:
            if (tuple(coord_pos),tuple(coord_vel)) in _dict:
                stuff.append((_dict[(tuple(coord_pos),tuple(coord_vel))],t - _dict[(tuple(coord_pos),tuple(coord_vel))]));
                break;
            _dict[(tuple(coord_pos),tuple(coord_vel))] = t;
            v = coord_pos.copy();
            for i in range(0,len(coord_pos)):
                delta = 0;
                for x in v:
                    if x > coord_pos[i]:
                        delta = delta + 1;
                    elif x < coord_pos[i]:
                        delta = delta - 1;
                coord_vel[i] = coord_vel[i] + delta; 
                coord_pos[i] = coord_pos[i] + coord_vel[i];
            t = 1 + t;
    
    lcm = 1;
    print(stuff);
    for x in stuff:
        lcm = int(numpy.lcm(lcm,x[1]));
    mi_time = max(lcm,min([x[0] for x in stuff]));
    print(int((mi_time + lcm - 1)/ lcm) * lcm);

__main__();
