#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int t;
int n,k;
string s;
string adj[105];

int fact[105];
int gr_in[105];
int gr_out[105];

int main(){

    fact[0] = 1;

    for(int i = 1;i <= 100;i++){
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }

    cin >> t;

    while(t--){
        cin >> n >> k;
        cin >> s;
        s = " " + s;

        for(int i = 1;i <= n;i++){
            gr_in[i] = 0;
            gr_out[i] = 0;
        }

        for(int i = 1;i <= n;i++){
            cin >> adj[i];
            adj[i] = " " + adj[i];
            for(int j = 1;j <= n;j++){
                if(adj[i][j] == '1'){
                    gr_in[j]++;
                    gr_out[i]++;
                }
            }
        }

        int ans = 1;

        for(int i = 1;i <= n;i++){
            if(s[i] == 'R'){
                ans = 1LL * ans * fact[gr_in[i]] % MOD;
            }else{
                ans = 1LL * ans * fact[gr_out[i]] % MOD;
            }
        }

        cout << ans << "\n";
    }


    return 0;
}
