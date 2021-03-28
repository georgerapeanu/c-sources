#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int MOD = 1e9 + 7;

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

int lgpow(int b,int e){
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


int n;
int dp[NMAX + 5];
int ways[NMAX + 5];
pair<int,int> v[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];
int father[NMAX + 5];
vector<int> graph[NMAX + 5];

FILE *f = fopen("arbset.in","r");
FILE *g = fopen("arbset.out","w");

class FenwickTree{
    int n;
    vector<int> aib;

public:

    FenwickTree(int n){
        this->n = n;
        this->aib = vector<int>(n + 1,0);
    };

    void update(int pos,int val){
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] = add(aib[pos],val);
        }
    }

    int query(int pos){
        int ans = 0;
        for(;pos;pos -= (-pos) & pos){
            ans = add(ans,aib[pos]);
        }
        return ans;
    }
    
    int query(int l,int r){
        return scad(query(r),query(l - 1));
    }
};

int last_id = 0;
void dfs(int nod,int tata){
    father[nod] = tata;
    l[nod] = ++last_id;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
    }
    r[nod] = last_id;
}

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i].first);
        v[i].second = i;
    }

    for(int i = 1;i < n;i++){
        int u,v;
        fscanf(f,"%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    dfs(1,0);

    FenwickTree aib_dp(n),aib_ways(n);

    for(int i = 1;i <= n;i++){
        int nod = v[i].second;
        ways[nod] = 1;
        dp[nod] = 1;

        for(auto it:graph[nod]){
            if(it == father[nod]){
                continue;
            }
            int fiu_ways = aib_ways.query(l[it],r[it]);
            int fiu_dp = aib_dp.query(l[it],r[it]);
            dp[nod] = add(mult(dp[nod],add(fiu_ways,1)),mult(fiu_dp,ways[nod]));
            ways[nod] = mult(ways[nod],add(fiu_ways,1));
        }
        aib_dp.update(l[nod],dp[nod]);
        aib_ways.update(l[nod],ways[nod]);
    }

    int ans = 0;

    for(int i = 1;i <= n;i++){
        ans = add(ans,dp[i]);
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
