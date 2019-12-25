#!/usr/bin/python3

dx = [-1,0,1,0];
dy = [0,1,0,-1];

def popcount(val):
    ans = 0;
    while val > 0:
        ans += (val & 1);
        val >>= 1;
    return ans;

#if requests from center we need to know the direction
def get_pos(states,direction,i,x,y):
    
    if i < 0 or i >= len(states):
        return 0;

    #if requests from outside we need to go to the other state
    if x < 0:
        return get_pos(states,0,i - 1,1,2);
    elif x > 4:
        return get_pos(states,2,i - 1,3,2);
    elif y < 0:
        return get_pos(states,3,i - 1,2,1);
    elif y > 4:
        return get_pos(states,1,i - 1,2,3);
    #if requests from center we need to know the direction
    
    if x == 2 and y == 2:
        ans = 0;
        for k in range(0,5):
            if direction == 0:
                ans += get_pos(states,direction,i + 1,4,k);
            elif direction == 1:
                ans += get_pos(states,direction,i + 1,k,0);
            elif direction == 2:
                ans += get_pos(states,direction,i + 1,0,k);
            else:
                ans += get_pos(states,direction,i + 1,k,4);
        return ans;
    pos = x * 5 + y;
    return (states[i] >> pos) & 1;

def afis(state):
    for x in range(0,5):
        for y in range(0,5):
            if x == 2 and y == 2:
                print("?",end = '');
            else:
                print(('#' if ((state >> (x * 5 + y)) & 1) == 1 else '.'),end = '');
        print();
    print();

def __main__():
    s = "";

    f = open("in","r");

    for line in f:
        s = s + (line.rstrip());

    state = 0;

    for x in range(0,len(s)):
        state |= int(1 if s[x] == '#' else 0) << x;

    cnt = 0;

    states = [state];

    while cnt < 200:
        print(cnt);
        n_states = [];

        states = list([0]) + states + list([0]);
        for l in range(0,len(states)):
            n_state = 0;
            for i in range(0,5):
                for j in range(0,5):
                    if i == 2 and j == 2:
                        continue;
                    tmp = 0;
                    for k in range(0,4):
                        tmp += get_pos(states,k,l,i + dx[k],j + dy[k]);
                    if get_pos(states,k,l,i,j) == 1:
                        n_state |= int(1 if tmp == 1 else 0) << (i * 5 + j);
                    else:
                        n_state |= int(1 if tmp == 1 or tmp == 2 else 0) << (i * 5 + j);
            n_states.append(n_state);
        
        states = list(n_states.copy());

        cnt += 1;

   
    ans = 0;

    for i in range(0,len(states)):
#        print(i);
#        afis(states[i]);
        ans += popcount(states[i]);
    print(ans);

__main__();
