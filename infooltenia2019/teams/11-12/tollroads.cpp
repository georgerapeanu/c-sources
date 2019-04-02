#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("tollroads.in","r");
FILE *g = fopen("tollroads.out","w");

const int NMAX = 1e5;
const int TMAX = 1e5;
const int QMAX = 1e2;

int n,m,q;

vector<pair<int,int> > graph[NMAX + 5];

vector<int> v;
vector<int> at_d[TMAX + 1];
int d[TMAX + 1];
int inq[NMAX + 5];

int query(int nod,int dist) {
    for(int i = 1; i <= n; i++) {
        d[i] = TMAX + 1;
        if(i == nod) {
            at_d[0].push_back(i);
            d[i] = 0;
        }
    }

    for(int h = 0; h <= dist; h++) {
        for(auto u:at_d[h]) {

            if(d[u] != h) {
                continue;
            }

            for(auto it:graph[u]) {
                if(d[it.first] > h + it.second) {
                    d[it.first] = h + it.second;
                    if(!inq[it.first]) {
                        inq[it.first] = 1;
                        v.push_back(it.first);
                    }
                }
            }
        }
        at_d[h].clear();

        for(auto it:v) {
            inq[it] = false;
            if(d[it] > dist) {
                continue;
            }
            at_d[d[it]].push_back(it);
        }

        v.clear();
    }

    int cnt = 0;

    for(int i = 1; i <= n; i++) {
        cnt += (d[i] <= dist);
    }

    return cnt - 1;
}

int main() {

    fscanf(f,"%d %d %d",&n,&m,&q);

    for(int i = 1; i <= m; i++) {
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        graph[x].push_back({y,z});
        graph[y].push_back({x,z});
    }

    while(q--) {
        int x,t;
        fscanf(f,"%d %d",&x,&t);
        fprintf(g,"%d\n",query(x,t));
    }


    fclose(f);
    fclose(g);

    return 0;
}
