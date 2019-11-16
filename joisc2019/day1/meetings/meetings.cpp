#include "meetings.h"
#pragma once
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

map<pair<int,int>,int> asked;
int lvl[2005];

int my_query(int u,int v,int w) {
    u--;
    v--;
    w--;

    if(v == u || w == u) {
        return u + 1;
    }

    if(v == w) {
        return v + 1;
    }

    // printf("%d %d %d\n",u,v,w);

    return Query(u,v,w) + 1;
}

void my_bridge(int u,int v) {
    u--;
    v--;
    if(u > v) {
        swap(u,v);
    }
    // printf("%d %d\n",u,v);
    Bridge(u,v);
}

void solve(int root,vector<int> &nodes) {
    for(int i = 0; i < (int)nodes.size(); i++) {
        if(nodes[i] == root) {
            swap(nodes[i],nodes.back());
            nodes.pop_back();
            break;
        }
    }

    if(nodes.size() == 0) {
        return;
    }
    if(nodes.size() == 1) {
        my_bridge(root,nodes[0]);
        return ;
    }

    int node = nodes[rand() % (int)nodes.size()];

    vector<int> path = {root,node};

    vector<pair<int,int> > subseq;

    for(auto it:nodes) {
        int tmp = my_query(root,it,node);
        if(tmp != node) {
            path.push_back(tmp);
        }
        subseq.push_back({tmp,it});
    }

    sort(path.begin(),path.end());
    path.resize(unique(path.begin(),path.end()) - path.begin());
    sort(path.begin(),path.end(),[&](int a,int b) {
        return my_query(root,a,b) == a;
    });

    sort(subseq.begin(),subseq.end());
    set<pair<int,int> > forb;

    for(int i = 1; i < (int)path.size(); i++) {
        my_bridge(path[i - 1],path[i]);
        forb.insert({path[i - 1],path[i]});
        forb.insert({path[i],path[i - 1]});
    }

    int lst = subseq[0].first;
    vector<int> tmp;

    for(int i = 0; i < (int)subseq.size(); i++) {
        if(subseq[i].first != lst) {
            solve(lst,tmp);
            lst = subseq[i].first;
            tmp.clear();
        }
        tmp.push_back(subseq[i].second);
    }
    solve(lst,tmp);
}

void Solve(int N) {
    srand(time(NULL));
    vector<int> nodes;
    for(int i = 1; i <= N; i++) {
        nodes.push_back(i);
    }
    solve(1,nodes);
}
