
#include <bits/stdc++.h>
#include <chrono>
#include <random>

using namespace std;

const int NMAX = 100;
const int inf = (1LL << 31) - 1;

int n;
int c[NMAX+5][NMAX+5];
int perm[NMAX + 5];
int _ans[NMAX + 5];

int nxt[NMAX + 5];
int ant[NMAX + 5];

void btr(int pas,int local_ans,int &ans){
    if(local_ans >= ans){
        return ;
    }
    if(pas > n){
        bool ok = true;

        for(int i = 1;i <= n && ok;i++){
            for(int j = i + 1;j <= n && ok;j++){
                if(c[i][perm[i]] < c[i][perm[j]] && c[j][perm[j]] < c[j][perm[i]]){
                    ok = false;
                }
            }
        }

        if(ok){
            ans = local_ans;
            for(int i = 1;i <= n;i++){
                _ans[i] = perm[i];
            }
        }

        return ;
    }

    for(int i = nxt[0];i != 0;i = nxt[i]){
        int u = ant[i];
        int v = nxt[i];
        nxt[u] = v;
        ant[v] = u;

        perm[pas] = i;
        btr(pas + 1,local_ans + c[pas][i],ans);
        nxt[u] = i;
        ant[v] = i;
    }
}

int main() {
    cin>>n;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
   
    for(int i = 0;i <= n;i++){
        nxt[i] = (i + 1) % (n + 1);
        ant[nxt[i]] = i;
    }

    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= n;j++) {
            cin >> c[i][j];
        }
    }
    
    int best = inf;
    btr(1,0,best);

    for(int i = 1;i <= n;i++) {
        cout << _ans[i] - 1 << ' ';
    }
}
