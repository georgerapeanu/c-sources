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

struct magic{
    map<int,long long> csts;
    set<pair<long long,int> > s;

    void insert(int pos){
        if(DEB)printf("insert %d\n",pos);
        csts[pos] = 0;
        s.insert({0,pos});
    }

    void erase(int pos){
        if(DEB)printf("erase %d\n",pos);
        s.erase({csts[pos],pos});
        csts.erase(pos);
    }

    void update(int pos,long long cost){
        if(DEB)printf("update %d %lld\n",pos,cost);
        s.erase({csts[pos],pos});
        csts[pos] = cost;
        s.insert({csts[pos],pos});
    }

    long long get_min(){
        if(DEB)printf("get min %lld\n",s.begin()->first);
        return s.begin()->first;
    }

};

int hsh(const vector<long long> &dp){
    int ans = 0;

    for(int i = 1;i < (int)dp.size();i++){
        ans = (1LL * ans * 23 + dp[i]) % MOD;
    }

    return ans;
}

int solve(int n, int k, int* v){



    vector<int> vals = {0};

    for(int i = 0;i < n;i++){
        vals.push_back(v[i]);
    }

    deque<int> dq = {0};
    vector<long long> dp(n + 1,1e18);
    dp[0] = 0;


    magic stuff;

    stuff.insert(0);

    for(int i = 1;i <= n;i++){
        while(dq.empty() == false && vals[dq.back()] <= vals[i]){
            stuff.erase(dq.back());
            dq.pop_back();
        }
        if(dq.empty() == false && dq.front() <= i - k){
            dq.pop_front();
            stuff.erase(dq.front());
        }
        if(i >= k){
            if(dq.empty() == false){
                stuff.update(dq.back(),dp[dq.back()] + vals[i]);
                dp[i] = stuff.get_min();
            }
            dq.push_back(i);
            stuff.insert(i);
            dp[i] = min(dp[i],vals[dq.front()] + (i >= k ? dp[i - k]:0));
        }
        else{
            dq.push_back(i);
            stuff.insert(i);
        }
        if(i == k){
            for(int i = k - 1;i > 0;i--){
                dp[i] = min(dp[i],dp[i + 1]);
            }

            for(int j = 0;j < (int)dq.size();j++){
                if(dq[j] < k){
                    stuff.update(dq[j],dp[j] + (j < (int)dq.size() ? vals[dq[j + 1]]:0));
                }
            }
        }
//        cout << "deb " << vals[dq.front()] + (i >= k ? dp[i - k]:0) << endl;
    }

    if(DEB){for(int i = 1;i <= n;i++)cout << dp[i] << " ";cout << "\n";}

    return hsh(dp);
}
