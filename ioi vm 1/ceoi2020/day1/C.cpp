#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

vector<int> graph[NMAX + 5];
int down_dp[NMAX + 5];
int dp[NMAX + 5];
int link[NMAX + 5];
int ans = 0;
int n;
long long d;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

void predfs(int nod,int tata){
    down_dp[nod] = 0;
    link[nod] = -1;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        down_dp[nod] |= !down_dp[it];
        if(down_dp[it] == 0){
            if(link[nod] == -1){
                link[nod] = it;    
            }
            else{
                link[nod] = 0;
            }
        }
    }
}

int lgpow(int b,long long e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }
    return p;
}

int def0;
int loss[NMAX + 5];
int pierd[NMAX + 5];

void dfs(int nod,int tata){
    dp[nod] = 0;
    link[nod] = -1;
    
    for(auto it:graph[nod]){
        dp[nod] |= !down_dp[it];
        if(down_dp[it] == 0){
            if(link[nod] == -1){
                link[nod] = it;    
            }
            else{
                link[nod] = 0;
            }
        }
    }

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        if(link[nod] == it){
            int tmp = down_dp[nod];
            down_dp[nod] = 0;
            dfs(it,nod);
            down_dp[nod] = tmp;
        }
        else{
            int tmp = down_dp[nod];
            down_dp[nod] = dp[nod];
            dfs(it,nod);
            down_dp[nod] = tmp;
        }
    }
    def0 += (dp[nod] == 0);
}

void dfs2(int nod,int tata){
    if(down_dp[nod] == 0){
        ans = add(ans,loss[d - 1]);
        for(auto it:graph[nod]){
            if(it == tata){
                continue;
            }
            dfs2(it,nod);
        }
    }
    else if(link[nod] > 0){
        dfs2(link[nod],nod);
    }
}

int main(){

    scanf("%d %lld",&n,&d);
    if(n == 2){
    //    assert(ans == lgpow(n,d * 2));    
        printf("%d\n",lgpow(n,d * 2));
        return 0;
    }

    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    predfs(1,0);
    dfs(1,0);

    for(int i = 1;i <= n;i++){
        if(link[i] > 0){
            pierd[link[i]]++;
        }
    }
    
    loss[0] = def0;

    int coef_all = 0;
    int coef_loss = 0;
    for(int i = 1;i <= n;i++){
        if(dp[i] == 0){
            coef_all = add(coef_all,def0);
            coef_loss = add(coef_loss,scad(pierd[i],1));
            printf("%d adds %d %d\n",i,def0,pierd[i] - 1);
        }
        else{
            coef_all = add(coef_all,def0);
            coef_loss = add(coef_loss,pierd[i]);
            printf("%d adds %d %d\n",i,def0,pierd[i]);
        }
    }

    for(long long t = 1;t <= d;t++){
        loss[t] = add(loss[t],mult(lgpow(n,t * 2 - 1),coef_all));
        loss[t] = add(loss[t],mult(loss[t - 1],coef_loss));
    }
    for(int i = 1;i <= n;i++)printf("%d ",link[i]);printf("\n");
    for(int i = 1;i <= n;i++)printf("%d ",pierd[i]);printf("\n");
    predfs(1,0);
    dfs2(1,0);
    if(dp[1] == 0){
        ans = ans;
    }
    else{
        ans = scad(lgpow(n,d * 2),ans);
    }

    for(int i = 1;i <= n;i++)printf("%d ",dp[i]);printf("\n");

    printf("deb %d\n",loss[d - 1]);
    printf("%d\n",ans);
    

    return 0;
}
