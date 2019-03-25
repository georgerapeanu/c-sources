#include <bits/stdc++.h>

using namespace std;

const int LENMAX = 3e6;

const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};

int x,y;

char c[LENMAX + 5];

struct op_t {
    bool turn;
    int steps;
};
int ind;

int i32() {
    while(c[ind] < '0' || c[ind] > '9') {
        ind++;
    }

    int ans = 0;

    while(c[ind] >= '0' && c[ind] <= '9') {
        ans = ans * 10 + c[ind] - '0';
        ind++;
    }

    return ans;
}

map<int,int> alien;

int main() {
    int n,m;
    int q;
    int dir = 1;
    double speed;
    int k;

    scanf("%d %d\n",&n,&m);
    scanf("%d %d\n",&x,&y);

    fgets(c + 1,LENMAX + 5,stdin);

    vector<op_t> v;

    ind = 1;

    while(c[ind] != '\0' && c[ind] != '\n') {
        while(c[ind] == ' ') {
            ind++;
        }
        char tp = c[ind];
        ind++;
        int steps = i32();
        v.push_back({tp == 'T',steps});
    }

    vector<pair<int,int> > ans;

    ans.push_back({x,y});

    for(auto it:v) {
        if(it.turn == 1) {
            dir += it.steps;
            dir %= 4;
        }
        else {
            for(int i = 0; i < it.steps; i++) {
                x += dx[dir];
                y += dy[dir];
                ans.push_back({x,y});
            }
        }
    }

    scanf("%lf\n",&speed);
    scanf("%d\n",&k);

    for(int i = 0; i < k; i++) {
        int id,tick;
        scanf("%d\n",&tick);
        alien[i] = tick;
    }

    scanf("%d\n",&q);

    while(q--) {
        int tick,id;

        scanf("%d %d\n",&tick,&id);

        int i_tick = tick;

        tick -= alien[id];
        tick *= speed;
        tick = max(0,tick);
        printf("%d %d %d %d\n",i_tick,id,ans[tick].first,ans[tick].second);
    }


    return 0;
}
