#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>

using namespace std;

FILE *f = fopen("ramen.in","r");
FILE *g = fopen("ramen.out","w");

const int NMAX = 1e5;

struct event_t{
    int type,t,x;
    bool operator < (const event_t &other)const{
        if(t != other.t){
            return t < other.t;
        }
        return type < other.type;
    }
};

int n,d;

vector<event_t> v;

multiset<int> active;

map<pair<int,int>,int> inv;
map<int,int> fr;

int ans[NMAX + 5];

int main(){

    fscanf(f,"%d %d",&n,&d);

    for(int i = 1; i <= n;i++){
        int t,p;
        fscanf(f,"%d %d",&t,&p);
        v.push_back({1,t - p,p});
        v.push_back({2,t + d,0});
        fr[p]++;
        inv[{p,fr[p]}] = i;
    }

    sort(v.begin(),v.end());

    fr.clear();

    for(auto it:v){
        if(it.type == 1){
            active.insert(it.x);
        }
        else{
            fr[*active.begin()]++;
            ans[inv[{*active.begin(),fr[*active.begin()]}]] = it.t + *active.begin();
            active.erase(active.begin());
        }
    }

    for(int i = 1;i <= n;i++){
        fprintf(g,"%d\n",ans[i]);
    }

    return 0;
}
