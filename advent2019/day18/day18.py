#!/usr/bin/python3

from heapq import *

dx = [-1,0,1,0]
dy = [0,1,0,-1]
viz = {};
prev = {};

mask = {};
pos = {};

def dfs(x,y,maze,requiem):
    
    if 'a' <= maze[x][y] and maze[x][y] <= 'z':
        mask[ord(maze[x][y]) - ord('a')] = requiem;
    
    n_requiem = requiem;

    if 'A' <= maze[x][y] and maze[x][y] <= 'Z':
        n_requiem |= int(1 << (ord(maze[x][y]) - ord('A')));
    for k in range(0,4):
        xx = x + dx[k];
        yy = y + dy[k];
        if xx >= 0 and xx < len(maze) and yy >= 0 and yy < len(maze[xx]) and maze[xx][yy] != '#':
            if (xx,yy) not in viz:
                viz[(xx,yy)] = viz[(x,y)] + 1;
                prev[(xx,yy)] = (x,y);
                dfs(xx,yy,maze,n_requiem);
#            elif prev[(x,y)] != (xx,yy) and prev[(xx,yy)] != (x,y):
#                print("FUCK " + str(x) + " " + str(y));

dist = {};

def bfs(x,y,maze):
    q = [(x,y)];
    viz = {(x,y):0};
    (sx,sy) = (x,y);
    
    while len(q) > 0:
        x = q[0][0];
        y = q[0][1];
        dist[(sx,sy,x,y)] = viz[(x,y)];
#        print(sx,sy,x,y)
        q.pop(0);

        for k in range(0,4):
            xx = x + dx[k];
            yy = y + dy[k];
#            print(x,y,xx,yy,maze[xx][yy],((xx,yy) not in viz));
            if xx >= 0 and xx < len(maze) and yy >= 0 and yy < len(maze[xx]) and maze[xx][yy] != '#' and ((xx,yy) not in viz):
                viz[(xx,yy)] = 1 + viz[(x,y)];
                q.append((xx,yy));

def bfs2(start,dist,mask):
    q = [];
    heappush(q,(0,start));
    viz = {start:0};

    target_state = 0;

    for x in mask:
        target_state |= (1 << x);
    
    while len(q) > 0:
        state = heappop(q);
        print(state);

        if viz[state[1]] != state[0]:
            continue;
        
        if(state[1][0] == target_state):
            return state[0];

        start = state[1]; #(conf,[(x,y)])

        for i in range(0,ord('z') - ord('a') + 1):
            if i not in mask:
                continue;
            if ((start[0] >> i) & 1) == 0 and (mask[i] & start[0]) == mask[i]:
                n_list = list(start[1]);
                n_cost = viz[start];
                n_conf = (start[0] | (1 << i))

                ok = False;

                for k in range(0,len(n_list)):
                    if((n_list[k][0],n_list[k][1],pos[i][0],pos[i][1]) in dist):
                        n_cost += dist[(n_list[k][0],n_list[k][1],pos[i][0],pos[i][1])];
                        n_list[k] = (pos[i][0],pos[i][1]);
                        ok = True;
                        break;
                
                if ok == False:
                    print("pula");

                n_start = (n_conf,tuple(n_list));

                if (n_start not in viz) or (viz[n_start] > n_cost):
                    heappush(q,(n_cost,n_start));
                    viz[n_start] = n_cost;

def __main__():

    f = open("in","r");

    maze = [];

    for line in f:
        maze.append(str(line).rstrip());

    tmp = [];

    for i in range(0,len(maze)):
        for j in range(0,len(maze[i])):
            if maze[i][j] == '@':
                sx = i;
                sy = j;
                viz[(sx,sy)] = 0;
                prev[(sx,sy)] = (-1,-1);
                requiem = 0;
                tmp.append((sx,sy));
                dfs(sx,sy,maze,requiem);
            if 'a' <= maze[i][j] and maze[i][j] <= 'z':
                pos[ord(maze[i][j]) - ord('a')] = (i,j);

    print("done dfs");

    for i in range(0,len(maze)):
        for j in range(0,len(maze[i])):
            if ('a' <= maze[i][j] and maze[i][j] <= 'z') or maze[i][j] == '@':
                print("done bfs " + str(i) + " " + str(j))
                bfs(i,j,maze);

    print(bfs2((0,tuple(tmp)),dist,mask));

#    for i in range(0,len(maze)):
#        for j in range(0,len(maze[i])):
#            if maze[i][j] == '#':
#               print("#",end = ' ');
#           else:
#              print(viz[(i,j)],end = ' ');
#        print();
   

__main__();
