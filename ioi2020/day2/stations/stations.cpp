#include "stations.h"
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> graph[1005];

int lst;
void dfs(int nod,int tata,int lvl,vector<int> &labels){
    lst++;
    if(lvl == 0){
        labels[nod] = lst;
    }
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod,lvl ^ 1,labels);
    }
    if(lvl == 1){
        labels[nod] = lst;
    }
    lst++;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
    for(int i = 0;i < n;i++){
        graph[i].clear();
    }
	vector<int> labels(n);
	for (int i = 0; i < n - 1; i++) {
		graph[u[i]].push_back(v[i]);
		graph[v[i]].push_back(u[i]);
	}

    dfs(0,-1,0,labels);
    
    map<int,int> to_norm;

    for(auto it:labels){
        to_norm[it] = 0;
    }

    int lst = 0;

    for(auto &it:to_norm){
        it.second = ++lst;
    }

    for(auto &it:labels){
        it = to_norm[it];
    }

	return labels;
}

int find_next_station(int s, int t, vector<int> c) {
    sort(c.begin(),c.end());
    if(s < c[0]){
        int father = c.back();
        c.pop_back();
        if(t < s){
            return father;
        }
        for(int i = 0;i < (int)c.size();i++){
            if(c[i] >= t){
                return c[i];
            }
        }
        return father;
    }
    else{
        reverse(c.begin(),c.end());
        int father = c.back();
        c.pop_back();
        reverse(c.begin(),c.end());
        if(t > s){
            return father;
        }
        for(int i = (int)c.size() - 1;i >= 0;i--){
            if(c[i] <= t){
                return c[i];
            }
        }
        return father;
    }
}
