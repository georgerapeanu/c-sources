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


struct tower_t {
    int x,y;
    double damage,range;
};

struct alien_t {
    int spawn;
    double speed, health;
    double position;
};

map<int,tower_t> tower;
map<int,alien_t> alien;

map<int,int> locked;

vector<int> alive;

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

    double health;

    scanf("%lf %lf\n",&health,&speed);
    scanf("%d\n",&k);

    for(int i = 0; i < k; i++) {
        int tick;
        scanf("%d\n",&tick);
        alien[i] = {tick,speed,health,0};
        alive.push_back(i);
    }

    int t;

    double damage,range;

    scanf("%lf %lf\n",&damage,&range);

    scanf("%d\n",&t);

    for(int i = 0; i < t; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        tower[i] = {x,y,damage,range};
        locked[i] = -1;
    }

    auto dist = [&](alien_t &a,tower_t &b) {
        int x = ans[(int)a.position].first;
        int y = ans[(int)a.position].second;

        return (double)sqrt(1.0 * (b.x - x) * (b.x - x) + 1.0 * (b.y - y) * (b.y - y));
    };

    for(int tick = 1; 1; tick++) {

        for(auto &it:alive) {
            if(tick <= alien[it].spawn) {
                continue;
            }
            alien[it].position += alien[it].speed;
            if(alien[it].position >= (int)ans.size()) {
                printf("%d\nLOSS\n",tick);
                return 0;
            }
        }

        for(int i = 0; i < t; i++) {
            double bdist = 1e18;
            int b = -1;
            if(locked[i] == -1 || dist(alien[locked[i]],tower[i]) > tower[i].range || alien[locked[i]].health <= 0) {
                locked[i] = -1;
                for(auto &it:alive) {
                    if(alien[it].spawn <= tick) {
                        double d = dist(alien[it],tower[i]);
                        if((bdist > d || (bdist == d && b > it)) && d <= tower[i].range) {
                            b = it;
                            bdist = d;
                        }
                    }
                }
                locked[i] = b;
            }
        }

        for(int i = 0; i < t; i++) {
            if(locked[i] != -1) {
                alien[locked[i]].health -= tower[i].damage;
            }
        }

        vector <int> nalive;

        for(auto it:alive) {
            if(alien[it].health > 0) {
                nalive.push_back(it);
            }
        }

        alive = nalive;

        if(alive.empty()) {
            printf("%d\nWIN\n",tick);
            return 0;
        }

    }


    return 0;
}
