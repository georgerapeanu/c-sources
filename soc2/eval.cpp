#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

FILE *f = fopen("soc2.in","r");
FILE *f1 = fopen("soc2.out","r");
FILE *f2 = fopen("soc2.ok","r");

const int NMAX = 256;

int n,m;
int v[NMAX + 5];
set<pair<int,int> > edges;


int main() {

    int a,b;

    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);

    if(a != b) {
        if(a < b) {
            printf("WA there is a better profit\n");
        }
        else {
            printf("WA wait wut,you found something better\n");
        }
        while(true);
    }

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1; i <= m; i++) {
        int u,v;
        fscanf(f,"%d %d",&u,&v);
        edges.insert({u,v});
        edges.insert({v,u});
    }

    vector<int> vertecies;

    int tmp;
    int cost = 0;
    while(fscanf(f1,"%d",&tmp) == 1) {
        for(auto it:vertecies) {
            if(edges.count({it,tmp})) {
                printf("WA %d %d are enemies\n",it,tmp);
                while(true);
            }
        }
        vertecies.push_back(tmp);
        cost += v[tmp];
    }

    if(cost != a) {
        printf("WA cost is not the same with the one provided\n");
        printf("real cost %d provided %d\n",cost,a);
        while(true);
    }

    printf("OK\n");

    fclose(f);
    fclose(f1);
    fclose(f2);

    return 0;
}
