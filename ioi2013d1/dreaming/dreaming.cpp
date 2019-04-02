#include "dreaming.h"
#include <vector>
#include <algorithm>
#include <cstdio>
 
using namespace std;
 
const int NMAX = 1e5;
 
pair<int,int> link[NMAX + 5];
 
vector< pair<int,int> > graph[NMAX + 5];
 
bool viz[NMAX + 5];
 
struct data_t{
    int best_dist;
    int node;
};
 
 
data_t dfs(int nod,int tata){
    viz[nod] = true;
    data_t ans;
    ans.node = nod;
    ans.best_dist = 0;
 
    link[nod] = {-1,-1};
 
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        data_t tmp = dfs(it.first,nod);
        if(ans.best_dist <= tmp.best_dist + it.second){
            ans.best_dist = tmp.best_dist + it.second;
            ans.node = tmp.node;
            link[nod] = it;
        }
    }
 
    return ans;
}
 
 
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    int ans = 0;
 
    for(int i = 0;i < M;i++){
        graph[A[i]].push_back({B[i],T[i]});
        graph[B[i]].push_back({A[i],T[i]});
    }
 
    vector<int> d;
 
    for(int i = 0;i < N;i++){
        if(viz[i]){
            continue;
        }
 
        data_t tmp = dfs(i,-1);
        data_t aux = dfs(tmp.node,-1);
 
        vector<int> diam;
        int len = 0;
        diam.push_back(0);
        for(int node = tmp.node;link[node].first != -1;node = link[node].first){
            diam.push_back(link[node].second);
            len += diam.back();
        }
 
        ans = max(ans,len);
 
        int best = 1 << 30;
        int pref = 0;
 
        for(int i = 0;i < (int)diam.size();i++){
            pref += diam[i];
            best = min(best,max(pref,len - pref));
        }
        
        d.push_back(best);
    }
 
    sort(d.begin(),d.end());
    reverse(d.begin(),d.end());
 
    while(d[0] >= d.back() + L){
        ans = max(ans,d[0] + d.back() + L);
        d.pop_back();
    }
 
    int tmp = 1 << 30;
   
    if((int)d.size() >= 3){
        tmp = min(tmp,max(d[0] + d[1] + L,d[1] + d[2] + 2 * L));
        tmp = min(tmp,max(d[0] + d[2] + L,d[2] + d[1] + 2 * L));
    }
   
    else if((int)d.size() == 2){
        tmp = d[0] + d[1] + L;
    }
 
    else{
        tmp = 0;
    }
 
    ans = max(ans,tmp);
 
    return ans;
}
