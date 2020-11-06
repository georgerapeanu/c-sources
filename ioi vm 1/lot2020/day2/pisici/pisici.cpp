#include "pisici.h"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 1e5;

vector<int> graph[NMAX + 5];

long long real_ans = 0;

struct edge_t{
    int u,v;
    int p;

    int to(int x){
        return u ^ v ^ x;
    }
};

edge_t edges[2 * NMAX + 5];
int viz[NMAX + 5];
long long q[NMAX + 5];


bool cmp(const pair<long long,long long> &a,const pair<long long,long long> &b){
    return a.first + a.second < b.first + b.second;    
}

pair<long long,long long> sons[NMAX + 5];
int len;

long long dfs2(int edge){
    if(q[edge] == -1){

        q[edge] = 0;

        for(auto it:graph[edges[edge].v]){
            if(edges[it].v == edges[edge].u){
                continue;
            }
            q[edge] += edges[it].p;
        }

        for(auto it:graph[edges[edge].v]){
            if(edges[it].v == edges[edge].u){
                continue;
            }
            dfs2(it);
        }

        len = 0;
        for(auto it:graph[edges[edge].v]){
            if(edges[it].v == edges[edge].u){
                continue;
            }
            sons[++len] = {q[it],edges[it].p};
        }

        long long ans = 0;
        if(len == 0){
            ans = 0;
        }

        sort(sons + 1,sons + 1 + len,cmp);

        long long sum = 0;

        for(int i = 1;i <= len;i++){
            sum += sons[i].second;
        }
    
        long long mini = 1e18;
        long long sum2 = 0;
    
        for(int i = 1;i <= len;i++){
            long long cst = sum + mini;
            
            if(cst <= sons[i].first + sons[i].second){
                ans = max(ans,cst);
                break;
            }
            else{
                ans = max(ans,sons[i].first + sons[i].second);
            }

            mini = min(mini,sons[i].first - sum2);
            sum2 += sons[i].second;
        }
    
        q[edge] = min(ans,q[edge]);
    }


    return q[edge];
}

long long solve(int n, vector<int> t, vector<int> p) {

    int lst = -1;

    for(int i = 0;i < n - 1;i++){
        graph[i + 2].push_back(++lst);
        graph[t[i]].push_back(++lst);
        edges[lst - 1] = {i + 2,t[i],p[i]};
        edges[lst] = {t[i],i + 2,p[i]};
        q[lst - 1] = -1;
        q[lst] = -1;
    }


    for(int edge = 0;edge <= lst;edge += 2){
        real_ans = max(real_ans,edges[edge].p + min(dfs2(edge),dfs2(edge ^ 1)));
    }

    return real_ans;
}
