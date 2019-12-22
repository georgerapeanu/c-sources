#include "shoes.h"

#pragma once
#include <deque>
#include <algorithm>

using namespace std;

deque<int> left[200005];
deque<int> right[200005];
int aib[200005];
bool viz[200005];

void update(int pos,int val) {
    for(; pos <= 2e5 + 1; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int query(int pos) {
    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }
    return ans;
}

long long count_swaps(vector<int> s) {
    reverse(s.begin(),s.end());
    s.push_back(0);
    reverse(s.begin(),s.end());
    for(int i = 1; i < (int)s.size(); i++) {
        if(s[i] < 0) {
            left[-s[i]].push_back(i);
        }
        else {
            right[s[i]].push_back(i);
        }
        update(i,1);
    }

    long long ans = 0;

    for(int i = 1; i < (int)s.size(); i++) {
        if(viz[i] == true) {
            continue;
        }
        if(s[i] < 0) {
            int pos = right[-s[i]].front();
            right[-s[i]].pop_front();
            left[-s[i]].pop_front();
            update(pos,-1);
            viz[pos] = true;
            update(i,-1);
            viz[i] = true;
            ans += query(pos) - query(i);
        }
        else {
            int pos = left[s[i]].front();
            left[s[i]].pop_front();
            right[s[i]].pop_front();
            update(pos,-1);
            viz[pos] = true;
            ans += query(pos) - query(i - 1);
            update(i,-1);
            viz[i] = true;
        }
    }
    return ans;
}
