#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;
int v[NMAX + 5];
int pref[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
        pref[i] = pref[i - 1] + v[i];
    }

    vector<pair<int,int> > ans;

    for(int l = 1;l <= n;l++){
        int k = 0;
        while((1 << k) <= v[l]){
            k++;
        }
        for(int r = l + 2;r <= n && pref[r - 1] - pref[l] < (1 << k);r++){
            if((pref[r - 1] - pref[l]) == (v[r] ^ v[l])){
                ans.push_back({l,r});
            }
        }
    }

    for(int r = n;r > 0;r--){
        int k = 0;
        while((1 << k) <= v[r]){
            k++;
        }
        for(int l = r - 2;l > 0 && pref[r - 1] - pref[l] < (1 << k);l--){
            if((pref[r - 1] - pref[l]) == (v[r] ^ v[l])){
                ans.push_back({l,r});
            }
        }
    }

    sort(ans.begin(),ans.end());
    ans.resize(unique(ans.begin(),ans.end()) - ans.begin());

    printf("%d\n",(int)ans.size());

    return 0;
}
