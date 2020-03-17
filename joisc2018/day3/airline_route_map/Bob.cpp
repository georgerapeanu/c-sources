#include "Boblib.h"
#include <cassert>
#include <cstdio>
#pragma once
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e3;
const int LGMAX = 10;

static int gr[NMAX + LGMAX + 5];
static vector<int> graph[NMAX + LGMAX + 5];
int exp_gr[LGMAX + 2];
int tag[NMAX + LGMAX + 5];

bool maybe_power[LGMAX + 5];

void Bob( int n, int m, int a[], int b[] ) {
    for(int i = 0; i < m; i++) {
        gr[a[i] + 1]++;
        gr[b[i] + 1]++;
        graph[a[i] + 1].push_back(b[i] + 1);
        graph[b[i] + 1].push_back(a[i] + 1);
    }

    for(int h = 0; h < LGMAX; h++) {
        exp_gr[h]++;///from master
        exp_gr[h]++;///from prev
        if(h < LGMAX - 1) { ///from nxt
            exp_gr[h]++;
        }
        for(int i = 1; i <= n - LGMAX - 2; i++) {
            if((i >> h) & 1) {
                exp_gr[h]++;
            }
        }
    }


    sort(exp_gr,exp_gr + LGMAX);
    reverse(exp_gr,exp_gr + LGMAX);


    int master_node = -1;
    int control_node = -1;

    vector<int> power_nodes;

    for(int i = 1; i <= n; i++) {
        if(gr[i] == LGMAX) {
            sort(graph[i].begin(),graph[i].end(),[&](int a,int b) {
                return gr[a] > gr[b];
            });
            bool ok = true;
            for(int h = 0; h < LGMAX; h++) {
                ok &= (exp_gr[h] == gr[graph[i][h]]);
            }
            if(ok == false) {
                continue;
            }
            ///maybe i is master
            for(auto it:graph[i]) {
                maybe_power[it] = true;
            }

            int fst = -1;

            for(auto it:graph[i]) {
                int cnt = 0;
                for(auto it2:graph[it]) {
                    cnt += maybe_power[it2];
                }
                if(cnt == 1 && (fst == -1 || gr[fst] < gr[it])) {
                    fst = it;
                }
            }

            if(fst != -1) {
                master_node = i;
                for(auto it:graph[fst]) {
                    if(gr[it] == 1) {
                        control_node = it;
                        break;
                    }
                }
                while(true) {
                    int nxt = -1;
                    power_nodes.push_back(fst);
                    maybe_power[fst] = false;
                    for(auto it:graph[fst]) {
                        if(maybe_power[it]) {
                            nxt = it;
                            break;
                        }
                    }
                    if(nxt == -1) {
                        break;
                    }
                    fst = nxt;
                }
                break;
            }

            for(auto it:graph[i]) {
                maybe_power[it] = false;
            }
        }
    }

    ///detect and sort power_nodes

    assert(master_node != -1);

    tag[master_node] = -1;
    tag[control_node] = -1;

    for(auto it:power_nodes) {
        tag[it] = -1;
    }

    for(int i = 0; i < LGMAX; i++) {
        for(auto it:graph[power_nodes[i]]) {
            if(tag[it] != -1) {
                tag[it] |= (1 << i);
            }
        }
    }

    vector<pair<int,int> > edges;

    for(int i = 0; i < m; i++) {
        if(tag[a[i] + 1] != -1 && tag[b[i] + 1] != -1) {
            edges.push_back({tag[a[i] + 1],tag[b[i] + 1]});
        }
    }

    InitMap(n - LGMAX - 2,edges.size());

    for(auto it:edges) {
        MakeMap(it.first - 1,it.second - 1);
    }
}

