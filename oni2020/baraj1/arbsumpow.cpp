#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 1e5;

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

int n;
int p;
int v[NMAX + 5];
int comb[10][10];
vector<int> sons[NMAX + 5];

struct node_t{
    int sums[10];

    node_t(){
        memset(sums,0,sizeof(sums));
    }

    node_t(int value){
        sums[0] = 1;
        for(int i = 1;i <= p;i++){
            sums[i] = mult(sums[i - 1],value);
        }
    }

    node_t operator + (const node_t &other)const{
        node_t ans;

        for(int i = 0;i <= p;i++){
            ans.sums[i] = this->sums[i];
            for(int j = 0;j <= i;j++){
                ans.sums[i] = add(ans.sums[i],mult(comb[i][j],mult(this->sums[j],other.sums[i - j])));
            }
        }

        return ans;
    }

    void debug(){
        for(int i = 0;i <= p;i++){
            printf("%d ",sums[i]);
        }
        printf("\n");
    }
};

node_t dp[NMAX + 5];

void dfs(int nod){
    dp[nod] = node_t(v[nod]);

    for(auto it:sons[nod]){
        dfs(it);
        dp[nod] = dp[nod] + dp[it];
    }
}

int main(){

    scanf("%d %d",&n,&p);

    for(int i = 0;i <= p;i++){
        comb[i][0] = comb[i][i] = 1;

        for(int j = 1;j < p;j++){
            comb[i][j] = add(comb[i - 1][j],comb[i - 1][j - 1]);
        }
    }

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 2;i <= n;i++){
        int father;
        scanf("%d",&father);
        sons[father].push_back(i);
    }

    dfs(1);
    
    int ans = 0;

    for(int i = 1;i <= n;i++){
        ans = add(ans,dp[i].sums[p]);
    }

    printf("%d\n",ans);

    return 0;
}
