#include "bubblesort2.h"
#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

const int NMAX = 5e5;
const int inf = 1 << 28;
const int VMAX = 1e6;

int aint[4 * VMAX + 5];
int cnt_less[4 * VMAX + 5];
int lazy[4 * VMAX + 5];
set<int> wh[VMAX + 5];

void propag(int nod,int st,int dr) {
    if(lazy[nod] == 0 || st == dr) {
        return ;
    }

    aint[2 * nod] -= lazy[nod];
    cnt_less[2 * nod] += lazy[nod];
    lazy[2 * nod] += lazy[nod];

    aint[2 * nod + 1] -= lazy[nod];
    cnt_less[2 * nod + 1] += lazy[nod];
    lazy[2 * nod + 1] += lazy[nod];

    lazy[nod] = 0;
}

void update(int nod,int st,int dr,int pos,int val,bool mode) {
    propag(nod,st,dr);

    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        if(mode == false) {
            wh[pos].erase(val);
        }
        else {
            wh[pos].insert(val);
        }

        aint[nod] = (wh[pos].empty() ? -inf:*wh[pos].rbegin()) - cnt_less[nod];
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val,mode);
    update(nod * 2 + 1,mid + 1,dr,pos,val,mode);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
}

void add_range(int nod,int st,int dr,int l,int r,int val) {
    propag(nod,st,dr);

    if(dr < l || st > r) {
        return ;
    }

    if(l <= st && dr <= r) {
        cnt_less[nod] += val;
        aint[nod] -= val;
        lazy[nod] += val;
        return ;
    }

    int mid = (st + dr) / 2;

    add_range(nod * 2,st,mid,l,r,val);
    add_range(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
}

vector<int> countScans(vector<int> A,vector<int> X,vector<int> V) {

    map<int,int> to_norm;

    for(auto it:A) {
        to_norm[it] = 1;
    }

    for(auto it:V) {
        to_norm[it] = 1;
    }

    int lst = 0;

    for(auto &it:to_norm) {
        it.second = ++lst;
    }

    for(int i = 0; i < (int)A.size(); i++) {
        update(1,1,lst,to_norm[A[i]],i + 1,1);
        add_range(1,1,lst,to_norm[A[i]],lst,1);
    }

    vector<int> answer;

    for(int i = 0; i < (int)X.size(); i++) {
        add_range(1,1,lst,to_norm[A[X[i]]],lst,-1);
        update(1,1,lst,to_norm[A[X[i]]],X[i] + 1,false);
        A[X[i]] = V[i];
        update(1,1,lst,to_norm[A[X[i]]],X[i] + 1,true);
        add_range(1,1,lst,to_norm[A[X[i]]],lst,1);

        answer.push_back(aint[1]);
    }

    return answer;
}
