#include "xylophone.h"
#pragma once
#include <algorithm>

using namespace std;

int ans[5005];

int a[5005];
int b[5005];

void solve(int n) {

    for(int i = 1; i < n; i++) {
        a[i] = query(i,i + 1);
    }
    for(int i = 1; i < n - 1; i++) {
        b[i] = query(i,i + 2);
    }

    int dir = 1;
    ans[1] = 0;
    ans[2] = a[1];

    for(int i = 3; i <= n; i++) {
        if(a[i - 2] + a[i - 1] != b[i - 2]) {
            dir *= -1;
        }
        ans[i] = ans[i - 1] + dir * a[i - 1];
    }

    pair<int,int> mi = {n + 5,n + 5},ma = {0,0};

    for(int i = 1; i <= n; i++) {
        mi = min(mi, {ans[i],i});
        ma = max(ma, {ans[i],i});
    }

    for(int i = 1; i <= n; i++) {
        ans[i] = ans[i] - mi.first + 1;
        if(mi.second > ma.second) {
            ans[i] = n - ans[i] + 1;
        }
        answer(i,ans[i]);
    }
}
