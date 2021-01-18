#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;
const int MOD = 1e9 + 7;

int n,m;
pair<int,int> v[NMAX + 5];

int father[NMAX + 5];
bool active[NMAX + 5];

int find_root(int nod){
    if(father[nod] == -1){
        return nod;
    }
    return father[nod] = find_root(father[nod]);
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

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        int k;
        scanf("%d",&k);
        int a = 0,b = 0;
        scanf("%d",&a);
        if(k == 2){
            scanf("%d",&b);
        }
        if(a < b){
            swap(a,b);
        }
        v[i] = {a,b};
    }

    for(int i = 0;i <= m;i++){
        father[i] = -1;
    }

    vector<int> ans;

    for(int i = 1;i <= n;i++){
        int a = v[i].first;
        int b = v[i].second;

        if(a == 0){
            continue;
        }
    
        if(active[a]){
            a = find_root(a);
        }

        if(b != 0 && active[b]){
            b = find_root(b);
        }

        if(a == b){
            a = b = 0;
        } 

        if(a < b){
            swap(a,b);
        }

        if(a == 0 && b == 0){
            continue;
        }
    
        father[a] = b;
        active[a] = true;
        ans.push_back(i);
    }

    int t = 1;

    for(int i = 0;i < (int)ans.size();i++){
        t *= 2;
        if(t >= MOD){
            t -= MOD;
        }
    }

    printf("%d %d\n",t,(int)ans.size());

    for(auto it:ans){
        printf("%d ",it);
    }

    return 0;
}
