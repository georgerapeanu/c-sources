#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n,q;
string s;

int sum[NMAX + 5];

int pref_max[NMAX + 5];
int pref_min[NMAX + 5];
int suff_max[NMAX + 5];
int suff_min[NMAX + 5];

int main(){

    cin >> t;

    while(t--){
        cin >> n >> q;

        cin >> s;

        s = " " + s;

        for(int i = 1;i <= n;i++){
            sum[i] = sum[i - 1] + (s[i] == '+' ? 1:-1);
        }

        sum[n + 1] = sum[n];

        for(int i = 1;i <= n + 1;i++){
            pref_max[i] = max(pref_max[i - 1],sum[i]);
            pref_min[i] = min(pref_min[i - 1],sum[i]);
        }
        
        suff_max[n + 2] = -1e9;
        suff_min[n + 2] = 1e9;

        for(int i = n + 1;i;i--){
            suff_max[i] = max(suff_max[i + 1],sum[i]);
            suff_min[i] = min(suff_min[i + 1],sum[i]);
        }
        
        while(q--){
            int l,r;
            cin >> l >> r;
            pair<int,int> pref = {pref_min[l - 1],pref_max[l - 1]};
            pair<int,int> suff = {suff_min[r + 1] - sum[r] + sum[l - 1],suff_max[r + 1] - sum[r] + sum[l - 1]};
            cout << max(pref.second,suff.second) - min(pref.first,suff.first) + 1 << "\n";
        }

    }   
    
    return 0;
}
