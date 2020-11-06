#!/usr/bin/python3
import helper;
import os;
import pygame;
import subprocess;
import math;
import time;


XMAX = 400;
YMAX = 400;
XRES = 1;
YRES = 1;
MOVE_UNIT = 1;
FAST_MOVE_UNIT = 10;

def drawPoint(screen,pos,color):
    pos2 = (int((float(pos[0]) + XMAX) * XRES),int((float(pos[1]) + YMAX) * YRES));
    if(pos2[0] < 0 or pos2[1] < 0 or pos2[0] >= XMAX * XRES * 2 or pos2[1] >= YMAX * YRES * 2):
        return ;
    pygame.draw.circle(screen,color,pos2,1);

def query(rover,distance,steeringAngle):
    subprocess.call("echo " + '"' + str(rover[0]) + " " + str(rover[1]) + " " + str(rover[2]) + " " + str(rover[3]) + " " + str(distance) + " " + str(steeringAngle) + '"' + ">in",shell=True);
    #print("echo " + '"' + str(rover[0]) + " " + str(rover[1]) + " " + str(rover[2]) + " " + str(rover[3]) + " " + str(distance) + " " + str(steeringAngle) + '"' + ">in");
    subprocess.call("./_level7<in>out",shell=True);
    f = open("out","r");
    for line in f:
        return line.rstrip().split(" ");


def __main__():
    ##initializations
    uid = helper.getRover("L7_M6DA04KF");    
    rover_data = helper.readRover(uid);
    print("uid is " + str(uid));
    print(rover_data);
    (wheelBase,maxSteerAngle,targetX,targetY,targetRadius) = tuple(rover_data.split(" "))
    direction = 0;
    
    ##game start
    pygame.init();
    pygame.event.pump();
    screen = pygame.display.set_mode([2 * XMAX * XRES,2 * YMAX * YRES]);
    drawPoint(screen,(targetX,targetY),(0,255,0));
    rover = (0,0,wheelBase,0);
    while True:
        newRover = query(rover,MOVE_UNIT,0);
        drawPoint(screen,(rover[0],rover[1]),(255,0,0));
        drawPoint(screen,(newRover[0],newRover[1]),(0,0,255));
        sensors = helper.getSensors(uid).split(" ");
        for i in range(0,15):
            ang = (float(rover[3]) + ((i - 8) * 55.00 / 7.00)) * math.acos(-1) / 180.00;
            xx = float(rover[0]) + float(sensors[i]) * math.sin(ang);
            yy = float(rover[1]) + float(sensors[i]) * math.cos(ang);
            drawPoint(screen,(xx,yy),(255,0,255));
        pygame.display.flip();

        pygame.event.pump();
        keys = pygame.key.get_pressed();

        while True:
            if(keys[pygame.K_RIGHT] or keys[pygame.K_LEFT] or keys[pygame.K_UP] or keys[pygame.K_DOWN]):
                break;
            pygame.event.pump();
            keys = pygame.key.get_pressed();
       

        print("got input");

        ang = -float(maxSteerAngle) * (int(keys[pygame.K_RIGHT]) - int(keys[pygame.K_LEFT]));
        distance = MOVE_UNIT * (int(keys[pygame.K_UP]) - int(keys[pygame.K_DOWN]));

        if keys[pygame.K_LSHIFT]:
            distance = distance * FAST_MOVE_UNIT / MOVE_UNIT;

        drawPoint(screen,(rover[0],rover[1]),(0,0,0));
        drawPoint(screen,(newRover[0],newRover[1]),(0,0,0));

        rover = query(rover,distance,ang);
        resp = helper.moveRover(uid,distance,ang);

        print(resp);
        print(rover);
    
        time.sleep(0.300);
        pygame.event.clear();

__main__();
