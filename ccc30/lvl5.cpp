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
                return {0,tick};
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

    t = min(500.0,gold / cost);

    srand(time(NULL));

    vector<pair<int,int> > stuff;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(in_path[ {i,j}] == 1) {
                continue;
            }
            stuff.push_back({i,j});;
        }
    }

    random_shuffle(stuff.begin(),stuff.end());
    t = min(t,(int)stuff.size());
    for(int i = 0; i < t; i++) {
        tower[i] = {stuff[i].first,stuff[i].second,damage,range,cost};
    }

    bool win = solve(ans).first;
    int cost = solve(ans).second;
    int when;

    const int TOTAL = 100;
    int REMATCH = 45;

    int init_cost = cost;

    while(win == false) {
        map<int,tower_t> tmp = tower;
        vector<pair<int,int> > tmp_stuff = stuff;
        for(int i = 0; i < t; i++) {
            if(rand() % TOTAL <= REMATCH) {
                int id = rand() % ((int)stuff.size() - t) + t;
                swap(stuff[i],stuff[id]);
                tower[i].x = stuff[i].first;
                tower[i].y = stuff[i].second;
            }
        }

        pair<int,int> a = solve(ans);

        if(a.first == 1 || a.second > cost) {
            ;
        }
        else {
            swap(tower,tmp);
            swap(tmp_stuff,stuff);
        }

        win = a.first;
    }

    fprintf(stderr,"%d %d %d %d",win,t,solve(ans).first,solve(ans).second);

    for(int i = 0; i < t; i++) {
        printf("%d %d\n",tower[i].x,tower[i].y);
    }

    return 0;
}
