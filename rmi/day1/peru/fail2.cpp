#include "peru.h"
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <iostream>
#include <cstdio>

using namespace std;

const int DEB = 0;
const int MOD = 1e9 + 7;
const int NMAX = 2500000;

int hsh(const vector<long long> &dp){
    int ans = 0;

    for(int i = 1;i < (int)dp.size();i++){
        ans = (1LL * ans * 23 + (dp[i] % MOD)) % MOD;
    }

    return ans;
}

vector<pair<int,int> > updates[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];

int solve(int n, int k, int* v){

    vector<int> vals(n + 1,0);

    for(int i = 0;i < n;i++){
        vals[i + 1] = v[i];
    }

    vector<int> st;

    for(int i = 1;i <= n;i++){
        while(st.empty() == false && vals[st.back()] < vals[i]){
            st.pop_back();
        }
        if(st.empty()){
            l[i] = 0;
        }
        else{
            l[i] = st.back();
        }
        st.push_back(i);
    }

    st.clear();

    for(int i = n;i >= 1;i--){
        while(st.empty() == false && vals[st.back()] <= vals[i]){
            st.pop_back();
        }
        if(st.empty()){
            r[i] = n + 1;
        }
        else{
            r[i] = st.back();
        }
        st.push_back(i);
    }

    for(int i = 1;i <= n;i++){
        int lst = i;
        for(int j = max(l[i],i - k);j < i;j++){
            while(lst < r[i] && lst <= j + k){
                updates[j].push_back({lst,vals[i]});
            }
        }
    }

    vector<long long> dp(n + 1,2e16);
    dp[0] = 0;

    if(DEB){
        for(int i = 1;i <= n;i++){
            cout << dp[i] << " ";
        }
        cout << endl;
    }

    return hsh(dp);
}
