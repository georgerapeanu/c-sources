#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
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

int fact[NMAX + 5];
int ifact[NMAX + 5];

void make_fact(){
    fact[0] = 1;

    for(int i = 1;i <= NMAX;i++){
        fact[i] = mult(fact[i - 1],i);
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1;i >= 0;i--){
        ifact[i] = mult(ifact[i + 1],i + 1);
    }
}

int comb(int n,int k){
    assert(0 <= k && k <= n);

    return mult(fact[n],mult(ifact[k],ifact[n - k]));
}

int t;
int n;
int v[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<int> graph_t[NMAX + 5];
int gr_in[NMAX + 5];
int gr_out[NMAX + 5];
int dp[NMAX + 5];
int sz[NMAX + 5];

int main(){

    make_fact();

    cin >> t;

    for(int test = 1;test <= t;test++){
        cout << "Case #" << test << ": ";

        cin >> n;

        for(int i = 1;i <= n;i++){
            graph[i].clear();
            graph_t[i].clear();
            gr_in[i] = 0;
            gr_out[i] = 0;
            dp[i] = 0;
            sz[i] = 0;
        }

        vector<int> visible;
       
        bool ok = true;
        for(int i = 1;i <= n;i++){
            int value;
            scanf("%d",&value);

            while((int)visible.size() + 1 > value){
                graph[visible.back()].push_back(i);
                graph_t[i].push_back(visible.back());
                gr_in[i]++;
                visible.pop_back();
            }
            if(visible.empty() == false){
                graph[i].push_back(visible.back());
                graph_t[visible.back()].push_back(i);
                gr_in[visible.back()]++;
            }
            visible.push_back(i);
            ok &= (visible.size() == value);
        }

        if(ok == false){
            cout << "0\n";
            continue;
        }

        vector<int> topo;

        for(int i = 1;i <= n;i++){
            if(gr_in[i] == 0){
                topo.push_back(i);
            }
        }

        for(int i = 0;i < (int)topo.size();i++){
            int nod = topo[i];

            for(auto it:graph[nod]){
                gr_in[it]--;
                if(gr_in[it] == 0){
                    topo.push_back(it);
                }
            }
        }

        int last_dp = 0;
        for(auto nod:topo){
            dp[nod] = 1;
            sz[nod] = 0;
            for(auto it:graph_t[nod]){
                if(gr_out[it] == 0){
                    dp[nod] = mult(dp[nod],dp[it]);
                    dp[nod] = mult(dp[nod],comb(sz[nod] + sz[it],sz[nod]));
                    sz[nod] = add(sz[nod],sz[it]);
                }
                gr_out[it]++;
            }
            sz[nod]++;
            last_dp = dp[nod];
        }
        
        cout << last_dp;
        cout << "\n";
    }

    return 0;
}
