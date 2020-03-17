#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("oracol.in","r");
FILE *g = fopen("oracol.out","w");

int n;
vector<pair<int,pair<int,int> > > edges;

int dsu[1005];

int fi_root(int nod){
    if(dsu[nod] == 0){
        return nod;
    }
    return dsu[nod] = fi_root(dsu[nod]);
}

bool unite(int x,int y){
    x = fi_root(x);
    y = fi_root(y);

    if(x == y){
        return false;
    }

    dsu[x] = y;
    return true;
}

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n + 1;j++){
            int val;
            fscanf(f,"%d",&val);
            edges.push_back({val,{i,j}});
        }
    }

    sort(edges.begin(),edges.end());

    int ans = 0;

    for(auto it:edges){
        ans += int(it.first) * unite(it.second.first,it.second.second);
    }

    fprintf(g,"%d",ans);

    fclose(f);
    fclose(g);

    return 0;
}
