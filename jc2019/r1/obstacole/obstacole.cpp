#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

FILE *f = fopen("obstacole.in","r");
FILE *g = fopen("obstacole.out","w");

int sweep_line = 0;
struct segm_t {
    int x,y,xx,yy;
    int id;

    bool operator < (const segm_t &other)const {
        double y_sect = (y == yy ? y : ((double(sweep_line - x) / double(xx - x)) * (yy - y) + y));
        double other_y_sect = (other.y == other.yy ? other.y:((double(sweep_line - other.x) / double(other.xx - other.x)) * (other.yy - other.y) + other.y));

        return y_sect < other_y_sect;
    }
};

const int NMAX = 1e5;
const int MMAX = 1e5;
const int XMAX = 1e9 + 1e4;

int n,m;
segm_t segm[2 * NMAX + 5];
int fa[2 * NMAX + 5];
int x[2 * NMAX + 5];
int y[2 * NMAX + 5];

vector<pair<pair<int,int>,int> > events;

int get_root(int nod) {
    if(fa[nod] == -1) {
        return nod;
    }
    return fa[nod] = get_root(fa[nod]);
}

const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

bool cmp_ev(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b) {
    if(a.first.first != b.first.first) {
        return a.first.first < b.first.first;
    }
    return a.second < b.second;
}

int main() {

    n = i32();
    m = i32();

    for(int i = 1; i <= n; i++) {
        fa[i] = -1;
        segm[i].x = i32();
        segm[i].y = i32();
        segm[i].xx = i32();
        segm[i].yy = i32();
        if(segm[i].x > segm[i].xx) {
            swap(segm[i].x,segm[i].xx);
            swap(segm[i].y,segm[i].yy);
        }
        segm[i].id = i;
        events.push_back(make_pair(make_pair(segm[i].x,i),0));
        events.push_back(make_pair(make_pair(segm[i].xx,i),2));

        if(segm[i].y > segm[i].yy) {
            x[i] = segm[i].x;
            y[i] = segm[i].y;
        }
        else {
            x[i] = segm[i].xx;
            y[i] = segm[i].yy;
        }
        events.push_back(make_pair(make_pair(x[i],i),1));
    }

    for(int i = 1; i <= m; i++) {
        fa[i + n] = -1;
        x[i + n] = i32();
        y[i + n] = i32();
        segm[i + n] = {x[i + n],y[i + n],x[i + n],y[i + n],i + n};
        events.push_back(make_pair(make_pair(x[i + n],i + n),1));
    }

    sort(events.begin(),events.end(),cmp_ev);

    set<segm_t> stuff;

    for(auto it:events) {
        sweep_line = it.first.first;
        if(it.second == 1) {
            set<segm_t> :: iterator _it = stuff.lower_bound({x[it.first.second],y[it.first.second],x[it.first.second],y[it.first.second],it.first.second});
            if(_it == stuff.end()) {
                fa[it.first.second] = -1;
            }
            else if(it.first.second <= n) {
                _it++;
                if(_it == stuff.end()) {
                    fa[it.first.second] = -1;
                }
                else {
                    fa[it.first.second] = _it->id;
                }
            }
            else {
                fa[it.first.second] = _it->id;
            }
        }
        else if(it.second == 0) {
            stuff.insert(segm[it.first.second]);
        }
        else {
            stuff.erase(segm[it.first.second]);
        }
    }

    for(int i = 1; i <= m; i++) {
        fprintf(g,"%d\n",x[get_root(i + n)]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
