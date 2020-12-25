#include "peru.h"
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <iostream>
#include <cstdio>

using namespace std;

const int DEB = 1;
const int MOD = 1e9 + 7;
const int NMAX = 2500000;

long long dp[NMAX + 5];

int hsh(int n){
    int ans = 0;

    for(int i = 1;i <= n;i++){
        ans = (1LL * ans * 23 + (dp[i] % MOD)) % MOD;
    }

    return ans;
}

int solve(int n, int k, int* v){

    vector<int> vals(n + 1,0);

    for(int i = 0;i < n;i++){
        vals[i + 1] = v[i];
        dp[i + 1] = 2e16;
    }

    deque<int> dq = {0};
    dp[0] = 0;

    for(int i = 1;i <= n;i++){
        while(dq.empty() == false && vals[dq.back()] < vals[i]){
            dq.pop_back();
        }
        if(dq.empty() == false && dq.front() < i - k){
            dq.pop_front();
        }
        dq.push_back(i);
        int lst = max(0,i - k);
        int bst = lst;
        for(int j = 0;j < (int)dq.size();j++){
            if(dp[i] > dp[lst] + vals[dq[j]]){
                bst = lst;
                dp[i] = min(dp[i],dp[lst] + vals[dq[j]]);
            }
            lst = dq[j];
        }
    }


    if(DEB){
        for(int i = 1;i <= n;i++){
            cout << dp[i] << " ";
        }
        cout << endl;
    }

    return hsh(n);
}
