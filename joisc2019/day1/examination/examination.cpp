#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct query_t {
    int a,b,c;
    int id;

    bool operator < (const query_t &other)const {
        if(c != other.c)return c > other.c;
        return id < other.id;
    }
};

class AIB2d {
public:
    int n;
    vector<vector<int> > stuff;
    vector<vector<int> > aib;

    AIB2d(int n) {
        this->n = n;
        stuff = vector<vector<int>>(n + 1,vector<int>(1,-1));
        aib = vector<vector<int>>(n + 1,vector<int>(1,-1));
    }

    void preupdate(int x,int y) {
        for(int xx = x; xx > 0; xx -= (-xx & xx)) {
            stuff[xx].push_back(y);
        }
    }

    void init() {
        for(int i = 1; i <= n; i++) {
            sort(stuff[i].begin(),stuff[i].end());
            stuff[i].resize(unique(stuff[i].begin(),stuff[i].end()) - stuff[i].begin());
            aib[i] = vector<int>(stuff[i].size(),0);
        }
    }

    void update(int x,int y,int val) {
        for(int xx = x; xx > 0; xx -= (-xx & xx)) {
            for(int yy = lower_bound(stuff[xx].begin(),stuff[xx].end(),y) - stuff[xx].begin(); yy > 0; yy -= (-yy & yy)) {
                aib[xx][yy] += val;
            }
        }
    }

    int query(int x,int y) {
        int ans = 0;

        for(int xx = x; xx <= n; xx += (-xx & xx)) {
            for(int yy = lower_bound(stuff[xx].begin(),stuff[xx].end(),y) - stuff[xx].begin(); yy < (int)stuff[xx].size(); yy += (-yy & yy)) {
                ans += aib[xx][yy];
            }
        }

        return ans;
    }
};

int n,q;
int ans[100005];
vector<query_t> events;

int main() {
    scanf("%d %d",&n,&q);

    map<int,int> to_norm;

    for(int i = 1; i <= n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        events.push_back({x,y,x + y,i - n});
        to_norm[x] = 1;
    }

    for(int i = 1; i <= q; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        events.push_back({a,b,c,i});
        to_norm[a] = 1;
    }

    sort(events.begin(),events.end());

    int last = 0;
    for(auto &it:to_norm) {
        it.second = ++last;
    }
    AIB2d aib(last);

    for(auto it:events) {
        if(it.id <= 0) {
            aib.preupdate(to_norm[it.a],it.b);
        }
    }

    aib.init();

    for(auto it:events) {
        if(it.id <= 0) {
            aib.update(to_norm[it.a],it.b,1);
        }
        else {
            ans[it.id] = aib.query(to_norm[it.a],it.b);
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
