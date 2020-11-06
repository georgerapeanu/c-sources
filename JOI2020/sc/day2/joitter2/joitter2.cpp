#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n,m;

int father[NMAX + 5];
set<int> in[NMAX + 5];
set<int> out[NMAX + 5];
set<int> nodes[NMAX + 5];

int find_root(int nod){
    if(father[nod] == 0){
        return nod;
    }
    return father[nod] = find_root(father[nod]);
}

long long unite(int x,int y){
    x = find_root(x);
    y = find_root(y);

    if(x == y){
        return false;
    }

    if(nodes[x].size() + in[x].size() + out[x].size() > nodes[y].size() + in[y].size() + out[y].size()){
        swap(x,y);
    }

    if((out[x].count(y) && out[y].count(x)) == 0){
        return 0;
    }

    long long delta = 0;

    delta -= 1LL * nodes[x].size() * in[x].size();
    delta -= 1LL * nodes[x].size() * nodes[x].size();
    delta -= 1LL * nodes[y].size() * in[y].size();
    delta -= 1LL * nodes[y].size() * nodes[y].size();

    father[x] = y;
    for(auto it:nodes[x]){
        nodes[y].insert(it);
        if(in[y].count(it)){
            in[y].erase(it);
        }
        if(out[y].count(it)){
            out[y].erase(it);
        }
    }

    for(auto it:in[x]){
        if(nodes[y].count(it)){
            continue;
        }
        in[y].insert(it);
        if(out[find_root(it)].count(x)){
            out[find_root(it)].erase(x);
            out[find_root(it)].insert(y);
        }
    }

    for(auto it:out[x]){
        if(nodes[y].count(it)){
            continue;
        }
        out[y].insert(it);
    }
    
    delta += 1LL * nodes[y].size() * in[y].size();
    delta += 1LL * nodes[y].size() * nodes[y].size();

    for(auto it:out[x]){
        delta += unite(x,it);
    }
    
    for(auto it:in[x]){
        delta += unite(x,it);
    }
    
    return delta;
}

long long add_edge(int x,int y){
    if(find_root(x) == find_root(y)){
        return 0;
    }


    long long delta = 0;

    delta -= 1LL * nodes[find_root(y)].size() * in[find_root(y)].size();
    delta -= 1LL * nodes[find_root(y)].size() * nodes[find_root(y)].size();

    out[find_root(x)].insert(find_root(y));
    in[find_root(y)].insert(x);

    delta += 1LL * nodes[find_root(y)].size() * in[find_root(y)].size();
    delta += 1LL * nodes[find_root(y)].size() * nodes[find_root(y)].size();
    delta += unite(x,y);

    return delta;
}

void afis(){
    printf("\n");
    for(int i = 1;i <= n;i++)printf("%d ",find_root(i));printf("\n");
    for(int i = 1;i <= n;i++){
        if(find_root(i) == i){
            printf("root %d\n",i);
            for(auto it:nodes[i])printf("%d ",it);printf("\n");
            for(auto it:in[i])printf("%d ",it);printf("\n");
            for(auto it:out[i])printf("%d ",it);printf("\n");
        }
    }
    printf("\n");
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        nodes[i].insert(i);
    }

    long long ans = 0;

    for(int i = 1;i <= m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        ans += add_edge(x,y);
        printf("%lld\n",ans);
    //    afis();
    }

    return 0;
}
