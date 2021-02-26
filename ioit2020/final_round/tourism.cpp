#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int BUCK = 320;
const int MOD = 1e9 + 7;

int n,m,q;
vector<int> graph[NMAX + 5];
bool viz[NMAX + 5];

int fr[BUCK + 5];
int real_value[BUCK + 5];
int v[NMAX + 5],len_v;
int real_value_v[NMAX + 5];

int dfs(int nod){
    int ans = 1;
    viz[nod] = true;

    for(auto it:graph[nod]){
        if(viz[it] == false){
            ans += dfs(it);
        }
    }

    return ans;
}

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int main(){

    scanf("%d %d %d",&n,&m,&q);

    for(int i = 1;i <= m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1;i <= n;i++){
        if(viz[i] == false){
            int len = dfs(i);
            if(len <= BUCK){
                fr[len]++;
            }else{
                v[++len_v] = len;
            }
        }
    }

    for(int i = 1;i <= BUCK;i++){
        real_value[i] = 1;
    }
    for(int i = 1;i <= len_v;i++){
        real_value_v[i] = 1;
    }

    for(int i = 1;i <= q;i++){
        int ans = 0;
        for(int val = 1;val <= BUCK;val++){
            real_value[val] = mult(real_value[val],val);
            ans = add(ans,mult(real_value[val],fr[val]));
        }
        for(int i = 1;i <= len_v;i++){
            real_value_v[i] = mult(real_value_v[i],v[i]);
            ans = add(ans,real_value_v[i]);
        }
        printf("%d ",ans);
    }

    return 0;
}

