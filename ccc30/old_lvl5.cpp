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

int t,n,m,k,q;
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
    double damage,range,cost;
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

map<pair<int,int>,bool > in_path;
map<pair<int,int>,bool> is_tower;

double health,spawn,damage,range,cost,speed;


pair<int,int> solve(vector<pair<int,int> > &ans) {
    alive.clear();

    for(int i = 0;i < k;i++){
        alive.push_back(i);
        alien[i].health = health;
        alien[i].position = 0;
    }

    for(int i =0; i < t;i++){
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
                return {-1,tick};
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
            return {1,tick};
        }
    }
}

int main() {
    int dir = 1;

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

    for(auto it:ans) {
        in_path[ {it.first,it.second}] = true;
    }

    scanf("%lf %lf\n",&health,&speed);
    scanf("%d\n",&k);

    for(int i = 0; i < k; i++) {
        int tick;
        scanf("%d\n",&tick);
        alien[i] = {tick,speed,health,0};
        alive.push_back(i);
    }


    double gold;

    scanf("%lf %lf %lf\n",&damage,&range,&cost);
    scanf("%lf\n",&gold);

    int lim = min(500.0,gold / cost);

    vector<pair<int,pair<int,int> > > positions;

    const int BUCK = 100;

    bool win = false;

    for(t = 0; t < lim; t++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(in_path[ {i,j}] || is_tower[ {i,j}]) {
                    continue;
                }
                int cnt = 0;
                for(auto it:ans) {
                    double d = sqrt(pow(it.first - i,2) + pow(it.second - j,2));
                    if(d <= range) {
                        cnt++;
                    }
                }
                positions.push_back({cnt,{i,j}});
            }
        }
        sort(positions.begin(),positions.end());
        reverse(positions.begin(),positions.end());

        int best_k = 0;
        pair<int,int> best_ans = {-1,1 << 30};
        for(int k = 0; k < min(BUCK,(int)positions.size()); k++) {
            tower[t].x = positions[k].second.first;
            tower[t].y = positions[k].second.second;
            tower[t].damage = damage;
            tower[t].range = range;
            tower[t].cost = cost;
            pair<int,int> c_ans = solve(ans);
            if(best_ans.first > c_ans.first) {
                continue;
            }

            if(c_ans.first == 1 && c_ans.second < best_ans.second) {
                best_ans = c_ans;
                best_k = k;
            }
            else if(c_ans.first == -1 && c_ans.second > best_ans.second) {
                best_ans = c_ans;
                best_k = k;
            }
        }
        tower[t].x = positions[k].second.first;
        tower[t].y = positions[k].second.second;
        tower[t].damage = damage;
        tower[t].range = range;
        tower[t].cost = cost;
        if(best_ans.first == 1) {
            win = true;
        }
        is_tower[ {tower[t].x,tower[t].y}] = true;
    }

    fprintf(stderr,"%d",win);

    for(int i = 0; i < lim; i++) {
        printf("%d %d\n",tower[i].x,tower[i].y);
    }

    return 0;
}
