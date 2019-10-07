#include "Joi.h"
#pragma once
#include <vector>
#include <functional>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 1e4;

void Joi(int N, int M, int A[], int B[], long long X, int T) {
    
    vector<int> graph[NMAX + 5];
    vector<int> children[NMAX + 5];
    int father[NMAX + 5];
    int h[NMAX + 5];

    bool viz[NMAX + 5];
    int lst = 0;

    memset(father,0,sizeof(father));
    memset(h,0,sizeof(h));
    memset(viz,0,sizeof(viz));

    function<void(int,const long long&)> dfs = [&](int nod,const long long &X){
        viz[nod] = true;

        h[nod] = 1;

        for(auto it:graph[nod]){
            if(viz[it] == true){
                continue;
            }
            children[nod].push_back(it);
            father[it] = nod;
            dfs(it,X);
            h[nod] = max(h[nod],1 + h[it]);
        }
    };

    function<void(int,const long long&)> dfs2 = [&](int nod,const long long &X){
        MessageBoard(nod,(X >> lst) & 1);
        lst = (lst + 1) % 60;
    
        for(auto it:children[nod]){
            dfs2(it,X);
        }
    };

    for(int i = 0;i < M;i++){
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }

    for(int i = 0;i < N;i++){
        sort(graph[i].begin(),graph[i].end());
    }

    dfs(1,X);
    
    for(int i = 0;i < N;i++){
        sort(children[i].begin(),children[i].end(),[&](int a,int b){return h[a] > h[b];});
    }

    dfs2(1,X);
}
