#include "Ioi.h"
#pragma once
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e4;

vector<int> graph[NMAX + 5];
vector<int> children[NMAX + 5];
int father[NMAX + 5];
int h[NMAX + 5];
int w[NMAX + 5];

bool viz[NMAX + 5];
int wut[NMAX + 5];
int lst = 0;

void dfs(int nod){
    viz[nod] = true;

    w[nod] = h[nod] = 1;

    for(auto it:graph[nod]){
        if(viz[it] == true){
            continue;
        }
        children[nod].push_back(it);
        father[it] = nod;
        dfs(it);
        w[nod] += w[it];
        h[nod] = max(h[nod],1 + h[it]);
    }
}

void dfs2(int nod){
    wut[nod] = lst;
    lst = (lst + 1) % 60;

    for(auto it:children[nod]){
        dfs2(it);
    }
}

int lim = 60;
bool take[NMAX + 5];

void dfs3(int nod){
    lim--;
    if(lim < 0){
        return;
    }

    take[nod] = true;
    
    for(auto it:children[nod]){
        dfs3(it);
    }
}

long long ans = 0;
long long v,p;

void dfs4(int nod){
    ans |= (v << wut[p]);
    
    for(auto it:children[nod]){
        if(take[it]){
            v = Move(p = it);
            dfs4(it);
            v = Move(p = nod);
        }
    }
}

void dfs5(int nod){
    ans |= (v << wut[p]);

    if(children[nod].empty() || take[children[nod][0]] == false){
        return ;
    }

    for(int i = 1;i < (int)children[nod].size();i++){
        if(take[children[nod][i]]){
            v = Move(p = children[nod][i]);
            dfs4(children[nod][i]);
            v = Move(p = nod);
        }
    }

    v = Move(p = children[nod][0]);
    dfs5(children[nod][0]);
}

long long Ioi(int N, int M, int A[], int B[], int P, int V, int T) {
    for(int i = 0;i < M;i++){
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }

    for(int i = 0;i < N;i++){
        sort(graph[i].begin(),graph[i].end());
    }

    dfs(1);
    for(int i = 0;i < N;i++){
        sort(children[i].begin(),children[i].end(),[&](int a,int b){return h[a] > h[b];});
    }

    dfs2(1);

    ans |= (((long long)V) << (wut[P]));

    while(w[P] < 60){
        V = Move(father[P]);
        P = father[P];
        ans |= (((long long)V) << (wut[P]));
    }
    
    v = V;
    p = P;

    dfs3(P);
    dfs5(P);

    return ans;
}
