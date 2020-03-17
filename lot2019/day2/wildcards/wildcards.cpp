#include <cstdio>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

const int NMAX = 1e4;

bool in_centroid[NMAX + 5];
int weight[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<string> ans;
int n;

set<pair<int,int> > nodes;///(length,node)

pair<int,string> father_edge[3 * NMAX + 5];

void dfs(int nod,int tata) {
    weight[nod] = 1;
    for(auto it:graph[nod]) {
        if(it == tata || in_centroid[it]) {
            continue;
        }
        dfs(it,nod);
        weight[nod] += weight[it];
    }
}

void apply_string(int nod,int tata,const string &s) {
    ans[nod] += s;

    for(auto it:graph[nod]) {
        if(it == tata || in_centroid[it]) {
            continue;
        }
        apply_string(it,nod,s);
    }
}

void centroid(int nod) {
    dfs(nod,-1);

    int tata = -1;
    int centr = nod;
    int total = weight[nod];

    while(true) {
        int bst_nod = -1;

        for(auto it:graph[centr]) {
            if(it == tata || in_centroid[it]) {
                continue;
            }
            if(bst_nod == -1 || weight[bst_nod] < weight[it]) {
                bst_nod = it;
            }
        }
        if(bst_nod == -1 || weight[bst_nod] * 2 <= total) {
            break;
        }
        tata = centr;
        centr = bst_nod;
    }

    in_centroid[centr] = true;

    //printf("took centroid %d with total %d and weight %d\n",centr,total,weight[centr]);


    for(auto it:graph[centr]) {
        if(in_centroid[it] == false) {
            centroid(it);
        }
    }

    ///apply id
    nodes.clear();
    for(auto it:graph[centr]) {
        if(in_centroid[it] == false) {
            nodes.insert({ans[it].size(),it});
            father_edge[it] = {-1,""};
        }
    }

    int lst_id = n;

    while(nodes.size() > 1) {
        pair<int,int> fst = *nodes.begin();
        nodes.erase(fst);
        pair<int,int> snd = *nodes.begin();
        nodes.erase(snd);
        string tmp = "";
        while(fst.first != snd.first) {
            fst.first++;
            tmp += "0";
        }
        lst_id++;
        father_edge[lst_id] = {-1,""};
        nodes.insert({fst.first + 1,lst_id});
        father_edge[fst.second] = {lst_id,tmp + "0"};
        father_edge[snd.second] = {lst_id,"1"};
    }

    for(int i = lst_id; i > n; i--) {
        if(father_edge[i].first != -1) {
            father_edge[i].second += father_edge[father_edge[i].first].second;
        }
    }


    for(auto it:graph[centr]) {
        if(in_centroid[it] == false) {
            if(father_edge[it].first != -1) {
                father_edge[it].second += father_edge[father_edge[it].first].second;
            }
            apply_string(it,centr,father_edge[it].second);
        }
    }

    ///connect current node
    if(nodes.size()) {
        while(nodes.begin()->first > (int)ans[centr].size()) {
            ans[centr] += '?';
        }
    }
    apply_string(centr,-1,"0");

    for(auto it:graph[centr]) {
        if(in_centroid[it] == false) {
            ans[it].back() = '?';
        }
    }

    ans[centr].back() = '1';

    in_centroid[centr] = false;

    //printf("return\n");
}

vector<string> patterns(vector<pair<int,int> > edges) {
    n = (int)edges.size() + 1;
    ans = vector<string>(n,string());


    for(auto &it:edges) {
        it.first--;
        it.second--;
        graph[it.first].push_back(it.second);
        graph[it.second].push_back(it.first);
    }

    centroid(0);


    return ans;
}

int main() {
    vector<pair<int,int> > edges;

    int n;

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        edges.push_back({x,y});
    }

    vector<string> tmp = patterns(edges);

    for(auto it:tmp) {
        cout << it << "\n";
    }

    return 0;
}
