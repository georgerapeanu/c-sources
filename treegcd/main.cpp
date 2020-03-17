#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("treegcd.in","r");
FILE *g = fopen("treegcd.out","w");

const int MOD = 1e9 + 7;

vector<int> divi[10005];

vector<int> graph[105];

int n,m;
int dp[105][10005];
int mobius[10005];
bool comp[10005];
int tmp[10005];

int add(int x,int y){
    x += y;
    if(x >= MOD){
        x -= MOD;
    }
    return x;
}

int scad(int x,int y){
    x -= y;
    if(x < 0){
        x += MOD;
    }
    return x;
}

int mult(int x,int y){
    return 1LL * x * y % MOD;
}

void dfs(int nod,int tata){
    for(int i = 1;i <= m;i++){
        dp[nod][i] = 1;
    }
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        for(int i = 1;i <= m;i++){
            tmp[i] = 0;
            for(int j = i;j <= m;j += i){
                tmp[i] = add(tmp[i],dp[it][j]);
            }
        }
        for(int i = 1;i <= m;i++){
            int val = tmp[1];
            for(auto it:divi[i]){
                if(mobius[it] == -1)val = scad(val,tmp[it]);
                else if(mobius[it] == 1)val = add(val,tmp[it]);
            }
            dp[nod][i] = mult(dp[nod][i],val);
        }
    }
}

int main(){

    comp[0] = comp[1] = true;

    for(int i = 1;i <= 10000;i++){
        mobius[i] = -1;
    }

    for(int i = 2;i <= 10000;i++){
        if(comp[i] == false){
            for(int j = i;j <= 10000;j += i){
                mobius[j] *= -1;
            }
            for(int j = i * i;j <= 10000;j += i * i){
                mobius[j] = 0;
            }
            for(int j = 2 * i;j <= 10000;j += i){
                comp[j] = true;;
            }
        }
    }

    for(int i = 1;i <= 10000;i++){
        for(int j = i;j <= 10000;j += i){
            divi[j].push_back(i);
        }
    }

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1;i < n;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    int ans = 0;

    for(int i = 1;i <= m;i++){
        ans = add(ans,dp[1][i]);
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
