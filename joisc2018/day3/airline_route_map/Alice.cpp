#include "Alicelib.h"
#include <cassert>
#include <cstdio>
#pragma once
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e3;
const int LGMAX = 10;

void Alice( int n, int m, int a[], int b[] ) {
    vector<pair<int,int> > edges;
    for(int i = 0; i < m; i++) {
        edges.push_back({a[i] + 1,b[i] + 1});
    }

    for(int h = 0; h < LGMAX; h++) {
        for(int i = 1; i <= n; i++) {
            if((i >> h) & 1) {
                edges.push_back({i,n + 1 + h});
            }
        }
    }

    for(int i = n + 1; i <= n + LGMAX; i++) {
        edges.push_back({n + LGMAX + 1,i});
        if(i > n + 1) {
            edges.push_back({i - 1,i});
        }
    }
    edges.push_back({n + LGMAX + 2,n + 1});

    InitG(n + LGMAX + 2,edges.size());

    for(int i = 0; i < (int)edges.size(); i++) {
        MakeG(i,edges[i].first - 1,edges[i].second - 1);
    }
}

