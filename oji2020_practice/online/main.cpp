#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

FILE *f = fopen("online.in","r");
FILE *g = fopen("online.out","w");

const int NMAX = 200;
const int MMAX = 10000;

int n,m,k;
vector<pair<int,pair<int,int> > > edges;
vector<pair<int,pair<int,int> > > tree;

int dsu[NMAX + 5];

void reset(){
    for(int i = 1;i <= n;i++){
        dsu[i] = -1;
    }
}

int fi_root(int nod){
    if(dsu[nod] < 0){
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

    if(dsu[x] < dsu[y]){
        dsu[x] += dsu[y];
        dsu[y] = x;
    }
    else{
        dsu[y] += dsu[x];
        dsu[x] = y;
    }

    return true;
}

int main(){

    fscanf(f,"%d %d",&n,&m);

    edges.reserve(m);

    for(int i = 1;i <= m;i++){
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        edges.push_back({z,{x,y}});
    }

    sort(edges.begin(),edges.end());

    int cost = 0;

    reset();

    tree.reserve(n);

    for(auto it:edges){
        if(unite(it.second.first,it.second.second)){
            cost += it.first;
            tree.push_back(it);
        }
    }

    fprintf(g,"%d\n",cost);

    fscanf(f,"%d",&k);

    while(k--){
        reset();
        pair<int,pair<int,int> > edge;
        fscanf(f,"%d %d %d",&edge.second.first,&edge.second.second,&edge.first);

        tree.push_back(edge);
        cost += edge.first;

        for(int i = n - 2;i >= 0 && tree[i].first > tree[i + 1].first;i--){
            swap(tree[i],tree[i + 1]);
        }

        for(int i = 0;i < n;i++){
            if(unite(tree[i].second.first,tree[i].second.second) == false){
                cost -= tree[i].first;
                for(int j = i;j < n - 1;j++){
                    tree[j] = tree[j + 1];
                }
                tree.pop_back();
                break;
            }
        }

        fprintf(g,"%d\n",cost);
    }

    fclose(f);
    fclose(g);

    return 0;
}
