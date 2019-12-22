#include "split.h"
#pragma once
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

vector<int> graph[NMAX + 5];
vector<int> sons[NMAX + 5];

bool special[NMAX + 5];

int low[NMAX + 5];
int id[NMAX + 5],last_id;
int weight[NMAX + 5];

int global_a;
int global_b;
int global_c;
int global_n;

bool found = false;
vector<int> ans;

void dfs2(int nod,int col,int &cnt) {
    if(cnt > 0) {
        cnt--;
        ans[nod] = col;
    }
    else {
        ans[nod] = 3;
    }

    for(auto it:sons[nod]) {
        dfs2(it,col,cnt);
    }
}

void dfs3(int nod,int col,int &cnt) {
    if(cnt > 0) {
        cnt--;
        ans[nod] = col;
    }
    else {
        ans[nod] = 3;
    }

    for(auto it:graph[nod]) {
        if(ans[it] == 0) {
            dfs3(it,col,cnt);
        }
    }
}

void dfs(int nod) {
    id[nod] = low[nod] = ++last_id;
    weight[nod] = 1;
    for(auto it:graph[nod]) {
        if(id[it] == 0) {
            dfs(it);
            sons[nod].push_back(it);
            weight[nod] += weight[it];
            low[nod] = min(low[nod],low[it]);
        }
        else {
            low[nod] = min(low[nod],id[it]);
        }
    }

    if(found) {
        return ;
    }

    if(weight[nod] >= global_a) {
        int tmp = weight[nod];

        for(auto it:sons[nod]) {
            if(low[it] < id[nod] && tmp - weight[it] >= global_a) {
                tmp -= weight[it];
                special[it] = true;
            }
        }

        if(tmp >= global_a && global_n - tmp >= global_b) {
            found = true;
            int how_many = global_a - 1;
            ans[nod] = 1;
            for(auto it:sons[nod]) {
                if(special[it] == true) {
                    continue;
                }
                dfs2(it,1,how_many);
            }
            how_many = global_b;
            dfs3(0,2,how_many);

        }
        else if(tmp >= global_b && global_n - tmp >= global_a) {
            found = true;
            int how_many = global_b - 1;
            ans[nod] = 2;
            for(auto it:sons[nod]) {
                if(special[it] == true) {
                    continue;
                }
                dfs2(it,2,how_many);
            }
            how_many = global_a;
            dfs3(0,1,how_many);
        }
    }
}

vector<int> find_split(int n, int a, int b, int c, vector<int> p, vector<int> q) {

    vector<int> perm = {0,1,2,3};

    if(b < a) {
        swap(a,b);
        swap(perm[1],perm[2]);
    }
    else if(c < a) {
        swap(a,c);
        swap(perm[1],perm[3]);
    }
    if(b > c) {
        swap(b,c);
        swap(perm[2],perm[3]);
    }

    global_a = a;
    global_b = b;
    global_c = c;
    global_n = n;

    ans.resize(n);

    for(int i = 0; i < (int)p.size(); i++) {
        graph[p[i]].push_back(q[i]);
        graph[q[i]].push_back(p[i]);
    }

    dfs(0);

    for(auto &it:ans) {
        it = perm[it];
    }

    return ans;
}
