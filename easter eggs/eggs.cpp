#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

vector<int> G[600];
int renumbered[600];
int inverse_renumber[600];


void renumber_dfs(int node,int father,int &val){
    renumbered[node] = val;
    inverse_renumber[val] = node;
    for(auto it:G[node]){
        if(it != father){
            renumber_dfs(it,node,++val);
        }
    }
}

vector<int> nodes;
bool ok(int le,int ri){
    nodes.clear();
    for(int i = le;i <= ri;i++){
        nodes.push_back(inverse_renumber[i]);
    }
    return query(nodes);
}

int findEgg (int N, vector < pair < int, int > > bridges){
    for(int i = 1;i <= N;i++){
        G[i].clear();
    }
    for(auto it:bridges){
        G[it.first].push_back(it.second);
        G[it.second].push_back(it.first);
    }
    int start = 1;
    renumber_dfs(1,0,start);


    int lo = 1,hi = N;
    while(hi - lo > 0){
        int mid = (lo + hi) / 2;
        if(ok(1,mid)){
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    return inverse_renumber[lo];
}
