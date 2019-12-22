#include "rect.h"

#pragma once
#include <vector>
#include <algorithm>

using namespace std;

int aib[2505][2505];
int n,m;
void update_aib(int x,int y,int val) {
    x++;
    y++;
    for(int i = x; i; i -= (-i) & i) {
        for(int j = y; j; j -= (-j) & j) {
            aib[i][j] += val;
        }
    }
}

int query_aib(int x,int y) {
    x++;
    y++;
    int ans = 0;
    for(int i = x; i <= m; i += (-i) & i) {
        for(int j = y; j <= n; j += (-j) & j) {
            ans += aib[i][j];
        }
    }
    return ans;
}


int lst = 0;
void reset_calc() {
    lst = 0;
}

int calc(int l,int r,vector<pair<pair<int,int>,int> > &v) {
    while(lst < (int)v.size() && v[lst].first.first > l) {
        lst++;
    }
    if(lst != (int)v.size() && v[lst].first == make_pair(l,r)) {
        return 1 + v[lst].second;
    }
    return 1;
}

long long count_rectangles(std::vector<std::vector<int> > a) {

    vector<pair<pair<int,int>,int> > v_heights;
    vector<pair<pair<int,int>,int> > tmp;

    n = a.size();
    m = a[0].size();

    long long ans = 0;

    vector<vector<int> > v_stack(m,vector<int>(0));
    vector<vector<vector<pair<pair<int,int>,int> > > > tervals(n,vector<vector<pair<pair<int,int>,int> > >(m,vector<pair<pair<int,int>,int> >(0)));
    for(int i = 0; i < n; i++) {
        vector<int> h_stack;
        v_heights.clear();
        for(int j = 0; j < m; j++) {
            tmp.clear();
            reset_calc();
            while(v_stack[j].size() > 0 && a[v_stack[j].back()][j] < a[i][j]) {
                tmp.push_back({{v_stack[j].back(),i},calc(v_stack[j].back(),i,v_heights)});
                v_stack[j].pop_back();
            }
            if(v_stack[j].size() > 0) {
                tmp.push_back({{v_stack[j].back(),i},calc(v_stack[j].back(),i,v_heights)});
            }
            while(v_stack[j].size() > 0 && a[v_stack[j].back()][j] <= a[i][j]) {
                v_stack[j].pop_back();
            }
            v_stack[j].push_back(i);
            v_heights = tmp;
            if(i > 0 && j < m - 1) {
                for(auto it:tervals[i - 1][j + 1]) {
                    if(it.first.first == j) {
                        continue;
                    }
                    update_aib(it.first.first,it.second,1);
                }

                for(auto it:v_heights) {
                    if(it.first.first == it.first.second - 1) {
                        continue;
                    }
                    ans += query_aib(max(0,j - it.second),it.first.second - it.first.first - 1);
                }

                for(auto it:tervals[i - 1][j + 1]) {
                    if(it.first.first == j) {
                        continue;
                    }
                    update_aib(it.first.first,it.second,-1);
                }
            }
        }
        for(int j = 0; j < m; j++) {
            reset_calc();
            while(h_stack.size() > 0 && a[i][h_stack.back()] < a[i][j]) {
                if(i > 0) {
                    tervals[i][j].push_back({{h_stack.back(),j},calc(h_stack.back(),j,tervals[i - 1][j])});
                }
                else {
                    tervals[i][j].push_back({{h_stack.back(),j},1});
                }
                h_stack.pop_back();
            }
            if(h_stack.size() > 0) {
                if(i > 0) {
                    tervals[i][j].push_back({{h_stack.back(),j},calc(h_stack.back(),j,tervals[i - 1][j])});
                }
                else {
                    tervals[i][j].push_back({{h_stack.back(),j},1});
                }
            }
            while(h_stack.size() > 0 && a[i][h_stack.back()] <= a[i][j]) {
                h_stack.pop_back();
            }
            h_stack.push_back(j);
        }
    }

    return ans;
}
