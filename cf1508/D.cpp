#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e3;

int n;
int x[NMAX + 5];
int y[NMAX + 5];
int p[NMAX + 5];
bool viz[NMAX + 5];

long long det(int xa,int ya,int xb,int yb,int xc,int yc){
    return 1LL * xa * (yb - yc) + 1LL * xb * (yc - ya) + 1LL * xc * (ya - yb);
}

class DisjointSetsUnion{
    int n;
    vector<int> father;

public:

    DisjointSetsUnion(int n){
        this->n = n;
        father = vector<int>(n + 5);
    }

    int find_root(int x){
        if(father[x] == 0){
            return x;
        }
        return find_root(father[x]);
    }

    bool unite(int x,int y){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            return false;
        }

        father[x] = y;

        return true;
    }

};

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d %d %d",&x[i],&y[i],&p[i]);
    }

    int bst = -1;

    for(int i = 1;i <= n;i++){
        if(p[i] != i){
            if(bst == -1 || make_pair(x[i],y[i]) < make_pair(x[bst],y[bst])){
                bst = i;
            }
        }
    }

    if(bst == -1){
        printf("0\n");
        return 0;
    }

    vector<int> order;

    for(int i = 1;i <= n;i++){
        if(p[i] != i && i != bst){
            order.push_back(i);
        }
    }

    sort(order.begin(),order.end(),[&](int a,int b){
        return det(x[bst],y[bst],x[a],y[a],x[b],y[b]) > 0;
    });


    DisjointSetsUnion dsu(n);
    
    for(int i = 1;i <= n;i++){
        if(viz[i] == false){
            for(int j = i;viz[j] == false;j = p[j]){
                dsu.unite(i,j);
                viz[j] = true;
            }
        }
    }

    vector<pair<int,int> > answer;

    for(int i = 0;i + 1 < (int)order.size();i++){
        if(dsu.find_root(order[i]) != dsu.find_root(order[i + 1])){
            answer.push_back({order[i],order[i + 1]});
            swap(p[order[i]],p[order[i + 1]]);
            dsu.unite(order[i],order[i + 1]);
        }
    }

    while(p[bst] != bst){
        answer.push_back({bst,p[bst]});
        swap(p[bst],p[p[bst]]);
    }

    printf("%d\n",(int)answer.size());

    for(auto it:answer){
        printf("%d %d\n",it.first,it.second);
    }

    return 0;
}
