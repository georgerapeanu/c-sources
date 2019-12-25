#!/usr/bin/python3

dx = [-1,0,1,0];
dy = [0,1,0,-1];


def __main__():
    
    k = 0; 
    L = -1;
    R = -2;
    A = [L,8,
         R,12,
         R,12,
         R,10,]
    B = [L,10,
         R,10,
         L,6]
    C = [R,10,
         R,12,
         R,10,]
    comm = A + C + A + C + B + B + C + A + C + B
   
    x = 0;
    y = 0;

    cells = {(0,0):'S'};
    
    mi_x = 0;
    ma_x = 0;
    mi_y = 0;
    ma_y = 0;

    for ind in comm:
        if ind == L:
            k = (k - 1 if k > 0 else 3);
        elif ind == R:
            k = (k + 1 if k < 3 else 0);
        else:
            for i in range(0,ind):
                x += dx[k];
                y += dy[k];
                cells[(x,y)] = '#';
                mi_x = min(mi_x,x);
                mi_y = min(mi_y,y);
                ma_x = max(ma_x,x);
                ma_y = max(ma_y,y);

    for x in range(mi_x,ma_x + 1):
        for y in range(mi_y,ma_y + 1):
            print((cells[(x,y)] if (x,y) in cells else '.'),end = '');
        print();

__main__();
