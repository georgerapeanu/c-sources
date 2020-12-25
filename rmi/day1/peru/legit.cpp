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
    map<long long,int> aux;///best without front
    ///aka {vals[dq[k]] + dp[dq[k - 1]]}

    for(int i = 1;i <= n;i++){
        while(dq.empty() == false && vals[dq.back()] <= vals[i]){
            if((int)dq.size() > 1){
                long long val = dp[dq[(int)dq.size() - 2]] + vals[dq.back()];
                aux[val]--;
                if(aux[val] == 0){
                    aux.erase(val);
                }
            }
            dq.pop_back();
        }
        if(dq.empty() == false && dq.front() <= i - k){
            if((int)dq.size() > 1){
                long long val = dp[dq[0]] + vals[dq[1]];
                aux[val]--;
                if(aux[val] == 0){
                    aux.erase(val);
                }
            }
            dq.pop_front();
        }
        if((int)dq.size() > 0){
            long long val = dp[dq.back()] + vals[i];
            aux[val]++;
        }
        dq.push_back(i);
        if(aux.empty() == false){
            dp[i] = min(dp[i],aux.begin()->first);
        }
        dp[i] = min(dp[i],dp[max(0,i - k)] + vals[dq.front()]);
    }


    if(DEB){
        for(int i = 1;i <= n;i++){
            cout << dp[i] << " ";
        }
        cout << endl;
    }

    return hsh(n);
}
