#include <bits/stdc++.h>

using namespace std;

const int inf = 1e6;

struct Zombie {
    int sx,sy,v;
    string moves;
};

struct Plant {
    int lx,ly;
    char dir;
};

map<int,int> to_norm_x,to_norm_y;
vector<int> inv_norm_x = {0};
vector<int> inv_norm_y = {0};

struct MyZombie : Zombie {
    int stx,drx;
    int sty,dry;

    void build() {
        stx = 0;
        drx = 0;
        sty = 0;
        dry = 0;
        int dx = 0;
        int dy = 0;

        for(auto it:moves) {
            dy += v * (it == 'U' ? 1:(it == 'D' ? -1:0));
            dx += v * (it == 'R' ? 1:(it == 'L' ? -1:0));
            dry = max(dry,dy);
            sty = min(sty,dy);
            drx = max(drx,dx);
            stx = min(stx,dx);
        }

        stx += sx;
        drx += sx;
        sty += sy;
        dry += sy;

        if(dx < 0) {
            stx = -inf;
        }
        if(dx > 0) {
            drx = inf;
        }
        if(dy < 0) {
            sty = -inf;
        }
        if(dy > 0) {
            dry = inf;
        }
    }
};

int n;
vector<MyZombie> zombie;

vector<Plant> get_best(vector<Plant> a,vector<Plant> b) {
    if(a.size() < b.size()) {
        return a;
    }
    return b;
}

bool cmp_x(MyZombie a,MyZombie b) {
    if(a.drx != b.drx) {
        return a.drx < b.drx;
    }
    return a.stx < a.stx;
}

bool cmp_y(MyZombie a,MyZombie b) {
    if(a.dry != b.dry) {
        return a.dry < b.dry;
    }
    return a.sty < a.sty;
}

pair<vector<Plant>,vector<Plant> > TryDoParalel(vector<MyZombie> &zombie,int breakpoint) {
    vector<Plant> ans_x;

    sort(zombie.begin(),zombie.end(),cmp_x);

    for(auto it:zombie) {
        if(ans_x.empty() || ans_x.back().lx < it.stx) {
            ans_x.push_back({it.drx,to_norm_y[-inf],'U'});
            if((int)ans_x.size() > breakpoint) {
                break;
            }
        }
    }


    vector<Plant> ans_y;

    sort(zombie.begin(),zombie.end(),cmp_y);

    for(auto it:zombie) {
        if(ans_y.empty() || ans_y.back().ly < it.sty) {
            ans_y.push_back({to_norm_x[-inf],it.dry,'R'});
            if((int)ans_x.size() > breakpoint) {
                break;
            }
        }
    }

    return make_pair(ans_x,ans_y);
}

class AIB {
    vector<int> aib;
public:
    AIB(int n) {
        aib.resize(n + 5);
    }

    void update(int pos,int val) {
        for(; pos < (int)aib.size(); pos += (-pos) & pos) {
            aib[pos] += val;
        }
    }

    int query(int pos) {
        int ans = 0;
        for(; pos; pos -= (-pos) & pos) {
            ans += aib[pos];
        }
        return ans;
    }
};

vector<Plant> TryDoPerpendicular(vector<MyZombie> &zombie) {
    vector<Plant> ans;
    ans.push_back({to_norm_x[inf],to_norm_y[inf],'L'});
    ans.push_back({to_norm_x[inf],to_norm_y[-inf],'U'});
    ans.push_back({to_norm_x[-inf],to_norm_y[-inf],'R'});
    ans.push_back({to_norm_x[-inf],to_norm_y[inf],'D'});
    for(int x = 1; x < (int)inv_norm_x.size(); x++) {
        vector<MyZombie> tmp;
        for(auto it:zombie) {
            if(it.stx <= x && it.drx >= x) {
                continue;
            }
            tmp.push_back(it);
        }
        vector<Plant> tmp_ans = TryDoParalel(tmp,2).second;
        if((int)tmp_ans.size() < 3) {
            tmp_ans.push_back({x,to_norm_y[-inf],'U'});
            ans = get_best(ans,tmp_ans);
        }
    }

    for(int y = 1; y < (int)inv_norm_y.size(); y++) {
        vector<MyZombie> tmp;
        for(auto it:zombie) {
            if(it.sty <= y && y <= it.dry) {
                continue;
            }
            tmp.push_back(it);
        }
        vector<Plant> tmp_ans = TryDoParalel(tmp,2).first;
        if((int)tmp_ans.size() < 3) {
            tmp_ans.push_back({to_norm_x[-inf],y,'R'});
            ans = get_best(ans,tmp_ans);
        }
    }

    return ans;
}

int main() {

    cin >> n;

    to_norm_x[-inf] = 1;
    to_norm_x[inf] = 1;
    to_norm_y[-inf] = 1;
    to_norm_y[inf] = 1;

    for(int i = 1; i <= n; i++) {
        MyZombie tmp;
        cin >> tmp.sx;
        cin >> tmp.sy;
        cin >> tmp.v;
        cin >> tmp.moves;
        tmp.build();
        zombie.push_back(tmp);
        to_norm_x[zombie.back().stx] = 1;
        to_norm_x[zombie.back().drx] = 1;
        to_norm_y[zombie.back().sty] = 1;
        to_norm_y[zombie.back().dry] = 1;
    }

    for(auto &it:to_norm_x) {
        it.second = inv_norm_x.size();
        inv_norm_x.push_back(it.first);
    }

    for(auto &it:to_norm_y) {
        it.second = inv_norm_y.size();
        inv_norm_y.push_back(it.first);
    }

    for(auto &it:zombie) {
        it.stx = to_norm_x[it.stx];
        it.sty = to_norm_y[it.sty];
        it.drx = to_norm_x[it.drx];
        it.dry = to_norm_y[it.dry];
    }

    vector<Plant> ans;
    ans.push_back({to_norm_x[inf],to_norm_y[inf],'L'});
    ans.push_back({to_norm_x[inf],to_norm_y[-inf],'U'});
    ans.push_back({to_norm_x[-inf],to_norm_y[-inf],'R'});
    ans.push_back({to_norm_x[-inf],to_norm_y[inf],'D'});

    ans = get_best(ans,TryDoParalel(zombie,3).first);///all lines are paralel
    ans = get_best(ans,TryDoParalel(zombie,3).second);///all lines are paralel
    ans = get_best(ans,TryDoPerpendicular(zombie));///there is at least one line for every direction

    printf("%d\n",(int)ans.size());

    for(auto it:ans) {
        printf("%d %d %c\n",inv_norm_x[it.lx],inv_norm_y[it.ly],it.dir);
    }

    return 0;
}

