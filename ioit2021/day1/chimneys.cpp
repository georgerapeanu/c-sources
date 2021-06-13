#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;

struct chimney_t{
    int a,b;
    int l;
};

struct edge_t{
    int to;
    int id;
    int cost;

    bool operator == (const edge_t &other)const{
        return this->to == other.to && this->id == other.id && this->cost == other.cost;
    }
};

int n;
chimney_t stuff[NMAX + 5];
edge_t link[NMAX + 5];
vector<edge_t> graph[2 * NMAX + 5];

long long ans = 1e18;
bool viz[2 * NMAX + 5];

long long dfs(int nod){
    viz[nod] = true;
    long long min1,min2;
    min1 = min2 = 1e18;
    for(auto it:graph[nod]){
        long long value = dfs(it.to) + it.cost;
        if(value < min1){
            min2 = min1;
            min1 = value;
            link[nod] = it;
        }else if(value < min2){
            min2 = value;
        }
    }
    ans = min(ans,min2);
    if(min1 == 1e18){
        min1 = 0;
    }
    return min1;
}

vector<vector<int> > to_afis;

void afis(int nod,bool linked){
    if(linked == false){
        to_afis.push_back(vector<int>());
    }

    if(link[nod].id != 0){
        to_afis.back().push_back(link[nod].id);
        afis(link[nod].to,true);
    }

    for(auto it:graph[nod]){
        if(link[nod] == it){
            continue;
        }
        afis(it.to,false);
    }
}

int main(){

    scanf("%d",&n);

    long long ans = 1e18;

    map<int,int> to_norm;

    for(int i = 1;i <= n;i++){
        scanf("%d %d %d",&stuff[i].a,&stuff[i].b,&stuff[i].l);
        to_norm[stuff[i].a] = 1;
        to_norm[stuff[i].b] = 1;
    }

    int last = 0;
    for(auto &it:to_norm){
        it.second = ++last;
    }
    
    for(int i = 1;i <= n;i++){
        stuff[i].a = to_norm[stuff[i].a];
        stuff[i].b = to_norm[stuff[i].b];
        graph[stuff[i].a].push_back({stuff[i].b,i,stuff[i].l});
    }

    for(int i = 1;i <= last;i++){
        if(!viz[i]){
            ans = min(ans,dfs(i));
            afis(i,false);
        }
    }

    printf("%d\n",(int)to_afis.size());

    for(auto it:to_afis){
        printf("%d\n",(int)it.size());
        for(auto it2:it){
            printf("%d ",it2 - 1);
        }
        printf("\n");
    }


    return 0;
}

