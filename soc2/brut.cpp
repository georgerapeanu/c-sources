#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

FILE *f = fopen("soc2.in","r");
FILE *g = fopen("soc2.ok","w");

const int NMAX = 256;

int n,m;
int v[NMAX + 5];
set<pair<int,int> > edges;
vector<int> active_vertecies;
vector<int> stuff;
int ans = 0;

void btr(int pas,int sum) {

    if(pas > n) {
        if(ans < sum) {
            ans = sum;
            stuff = active_vertecies;
        }
        return ;
    }

    btr(pas + 1,sum);

    for(auto it:active_vertecies) {
        if(edges.count({it,pas}) == 1) {
            return ;
        }
    }

    active_vertecies.push_back(pas);
    sum += v[pas];

    btr(pas + 1,sum);

    sum -= v[pas];
    active_vertecies.pop_back();
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1; i <= m; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        edges.insert({x,y});
        edges.insert({y,x});
    }

    btr(1,0);

    fprintf(g,"%d\n",ans);

    for(auto it:stuff) {
        fprintf(g,"%d ",it);
    }

    fclose(f);
    fclose(g);

    return 0;
}
