#include "peru.h"
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <iostream>
#include <cstdio>
#include <cassert>

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

struct node_t{
    long long val;
    long long mi;

    node_t(long long val){
        this->val = this->mi = val;
    }
};

struct my_stack_t{
    vector<node_t> v;

    void push(node_t tmp){
        if(v.size()){
            v.push_back(v.back());
            v.back().val = tmp.val;
            v.back().mi = min(v.back().mi,tmp.val);
        }
        else{
            v.push_back(tmp);    
        }
    }

    void pop(){
        v.pop_back();
    }

    bool empty(){
        return v.empty();
    }

    int size(){
        return v.size();
    }

    node_t top(){
        return v.back();
    }
};

struct my_deque_t{

    my_stack_t back;
    my_stack_t front;
    my_stack_t aux;

    void pop_front(){
        if(front.empty()){
            int sz = max(1,(int)back.size() / 2);
            while(back.size() > sz){
                node_t tmp = back.top();
                back.pop();
                aux.push(tmp);
            }
            while(back.size() > 0){
                node_t tmp = back.top();
                back.pop();
                front.push(tmp);
            }
            while(aux.size() > 0){
                node_t tmp = aux.top();
                aux.pop();
                back.push(tmp);
            }
        }
        front.pop();
    }
    void push_back(long long val){
        node_t tmp(val);
        back.push(tmp);
    }
    void pop_back(){
        if(back.empty()){
            int sz = max(1,(int)front.size() / 2);
            while(front.size() > sz){
                node_t tmp = front.top();
                front.pop();
                aux.push(tmp);
            }
            while(front.size() > 0){
                node_t tmp = front.top();
                front.pop();
                back.push(tmp);
            }
            while(aux.size() > 0){
                node_t tmp = aux.top();
                aux.pop();
                front.push(tmp);
            }
        }
        back.pop();
    }

    long long get_min(){

        long long ans = 1e18;
        if(front.empty() == false){
            ans = min(ans,front.top().mi);
        }
        if(back.empty() == false){
            ans = min(ans,back.top().mi);
        }
        return ans;
    }

    bool empty(){
        return front.empty() && back.empty();
    }

    int size(){
        return front.size() + back.size();
    }
};

int solve(int n, int k, int* v){

    vector<int> vals(n + 1,0);

    for(int i = 0;i < n;i++){
        vals[i + 1] = v[i];
        dp[i + 1] = 2e16;
    }

    deque<int> dq = {0};
    dp[0] = 0;
    my_deque_t stuff;
    
    for(int i = 1;i <= n;i++){
        while(dq.empty() == false && vals[dq.back()] <= vals[i]){
            if(stuff.empty() == false){
                stuff.pop_back();
            }
            dq.pop_back();
        }
        if(dq.empty() == false && dq.front() <= i - k){
            if(stuff.empty() == false){
                stuff.pop_front();
            }
            dq.pop_front();
        }
        if((int)dq.size() > 0){
            long long val = dp[dq.back()] + vals[i];
            stuff.push_back(val);
        }
        dq.push_back(i);
        if(stuff.empty() == false){
            dp[i] = min(dp[i],stuff.get_min());
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
