#include <bits/stdc++.h>

using namespace std;

class DSU{
    vector<int> father;
    vector<pair<int,int> > edges;
    vector<int> values;

public:
    
    DSU(int n,vector<int> init_values){
        father = vector<int>(n + 1); 
        values = init_values;
        edges.clear();
    }

    int find_root(int nod){
        if(father[nod] == 0){
            return nod;
        }
        return father[nod] = find_root(father[nod]);
    }

    bool unite(int x,int y,int z){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            return false;
        }

        if(z == values[x]){
            father[y] = x;    
            edges.push_back({y,x});
            return true;
        }else if(z == values[y]){
            father[x] = y;
            edges.push_back({x,y});
            return true;
        }

        father[x] = (int)father.size();
        father[y] = (int)father.size();
        edges.push_back({x,(int)father.size()});
        edges.push_back({y,(int)father.size()});
        father.push_back(0);
        values.push_back(z);
        return true;
    }

    void afis(){
        printf("%d\n",(int)values.size() - 1);
        for(int i = 1;i < (int)values.size();i++){
            printf("%d ",values[i]);
        }
        printf("\n");
        printf("%d\n",(int)father.size() - 1);

        for(auto it:edges){
            printf("%d %d\n",it.first,it.second);
        }
    }
};

int n;
int v[505][505];
vector<pair<int,pair<int,int>> > edges;

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            scanf("%d",&v[i][j]);
            edges.push_back({v[i][j],{i,j}});
        }
    }

    vector<int> values = {0};

    for(int i = 1;i <= n;i++){
        values.push_back(v[i][i]);
    }

    DSU dsu(n,values);

    sort(edges.begin(),edges.end());

    for(auto it:edges){
        dsu.unite(it.second.first,it.second.second,it.first); 
    }

    dsu.afis();

    return 0;
}
