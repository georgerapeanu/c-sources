#!/usr/bin/python
import collections;

dx = [-1,0,1,0];
dy = [0,1,0,-1];

def get(x,y,matrix):
    if x < 0 or x >= len(matrix) or y < 0 or y >= len(matrix[x]):
        return (-1,-1);
    elif matrix[x][y] == '.':
        return (x,y);
    elif matrix[x][y] == ' ' or matrix[x][y] == '#':
        return (-1,-1);
    else:
        for k in range(0,4):
#            print(x + dx[k],y + dy[k]);
            if 'A' <= matrix[x + dx[k]][y + dy[k]] and matrix[x + dx[k]][y + dy[k]] <= 'Z':
                if dx[k] + dy[k] < 0:
                    return str(matrix[x + dx[k]][y + dy[k]]) + str(matrix[x][y]);
                else:
                    return str(matrix[x][y]) + str(matrix[x + dx[k]][y + dy[k]]);

dist = {};
ant = {};
portals = collections.defaultdict(lambda:[]);    

def bfs(start,graph):
    q = [start];
    dist[start] = 0;
    ant[start] = -1;

    while len(q) > 0:
        start = q[0];
        q.pop(0);

#        print(start);

        if start == (portals["ZZ"][0],0):
            print(dist[start]);
            while start != -1:
#                print(start);
                start = ant[start];
            return ;

        for x in graph[start[0]]:
            neigh = (x[0],start[1] + x[1]);
            if (neigh not in dist) and neigh[1] >= 0:
                q.append(neigh)
                ant[neigh] = start;
                dist[neigh] = 1 + dist[start];
def __main__():
    matrix = [];

    f = open("in","r");

    for line in f:
        matrix.append(line);
        matrix[len(matrix) - 1] = matrix[len(matrix) - 1][:len(line) - 1:];
#        print matrix[len(matrix) - 1];
#    print(len(matrix));
    graph = collections.defaultdict(lambda:[]);    

    for x in range(2,len(matrix) - 2):
        for y in range(2,len(matrix[x]) - 2):
            if matrix[x][y] != '.':
                continue;
            for k in range(0,4):
                xx = x + dx[k];
                yy = y + dy[k];
                if get(xx,yy,matrix) != (-1,-1):
                    if isinstance(get(xx,yy,matrix),str) == True:
                        portals[get(xx,yy,matrix)].append(get(x,y,matrix));
                    else:

                        graph[get(x,y,matrix)].append((get(xx,yy,matrix),0));
                        graph[get(xx,yy,matrix)].append((get(x,y,matrix),0));
#                        print(get(x,y,matrix),get(xx,yy,matrix));
    
    for x in portals:
        if len(portals[x]) > 1:
            if portals[x][0][0] == 2 or portals[x][0][0] == len(matrix) - 3 or portals[x][0][1] == 2 or portals[x][0][1] == len(matrix[0]) - 3:
                graph[portals[x][0]].append((portals[x][1],-1));
            else:
                graph[portals[x][0]].append((portals[x][1],1));
            if portals[x][1][0] == 2 or portals[x][1][0] == len(matrix) - 3 or portals[x][1][1] == 2 or portals[x][1][1] == len(matrix[0]) - 3:
                graph[portals[x][1]].append((portals[x][0],-1));
            else:
                graph[portals[x][1]].append((portals[x][0],1));
                

    bfs((portals["AA"][0],0),graph);

__main__();
