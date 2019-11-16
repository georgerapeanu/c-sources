#include "minerals.h"

#pragma once
#include <vector>
#include <algorithm>

using namespace std;

bool my_query(int a) {
    static int last = 0;
    a = Query(a);
    int ans = a ^ last;
    last = a;
    return ans > 0;
}

void solve(const vector<int> &l,const vector<int> &r,bool mode) {
    if((int)l.size() == 1) {
        Answer(l[0],r[0]);
        return ;
    }

    int len = max(1,int(0.65 * (int)l.size()));

    if(mode == true) {
        for(int i = (int)l.size() - 1; i >= len; i--) {
            my_query(l[i]);
        }
    }
    else {
        len = (int)l.size() - len;
        for(int i = 0; i < len; i++) {
            my_query(l[i]);
        }
    }

    vector<int> v[2];

    for(auto it:r) {
        v[((int)v[0].size()) >= len || ((int)v[1].size() < (int)l.size() - len && my_query(it) == 1)].push_back(it);
    }

    vector<int> st[2];

    for(int i = 0; i < (int)l.size(); i++) {
        st[i >= len].push_back(l[i]);
    }

    solve(st[0],v[0],true);
    solve(st[1],v[1],false);

}

void Solve(int n) {
    vector<int> v[2];
    for(int i = 1; i <= 2 * n; i++) {
        v[my_query(i)].push_back(i);
    }
    solve(v[0],v[1],true);
}

