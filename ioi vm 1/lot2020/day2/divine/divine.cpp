#include "divine.h"
#include <cstdio>

using namespace std;

vector<pair<int,int> > edges;

bool in_comp[600];

void dfs(int root,vector<int> &nodes){
    if(nodes.empty()){
        return ;
    }

    vector<int> tmp;
    for(auto it:nodes){
        in_comp[it] = 0;
        if(it != root){
            tmp.push_back(it);
        }
    }
    nodes = tmp;
 /*   printf("root is %d\n",root);
    for(auto it:nodes)printf("%d ",it);
    printf("\n");
   */ 
    vector<vector<int> > comp;

    while(nodes.size()){ 
        int ans = query(nodes);
        comp.push_back(vector<int>());
        for(auto it:nodes){
            comp.back().push_back(it);
        }
        for(int i = 0;i < (int)comp.back().size();i++){
            vector<int> tmp;
            for(int j = 0;j < (int)comp.back().size();j++){
                if(i == j){
                    continue;
                }
                tmp.push_back(comp.back()[j]);
            }
            /*    printf("debbb\n");
                for(auto it:tmp)printf("%d ",it);
                printf("\n");*/
            if(query(tmp) == ans){
                comp.back() = tmp;
                i--;
            }
        }
        for(auto it:comp.back()){
            in_comp[it] = true;
        }
        vector<int> tmp;
        for(auto it:nodes){
            if(in_comp[it] == false){
                tmp.push_back(it);
            }
        }
        nodes = tmp;
    }
/*
    for(auto it:comp){
        for(auto it2:it)printf("%d ",it2);printf("\n");
    }
*/
    for(auto it:comp){
        int son = -1;
        for(auto it2:it){
            if(query({root,it2}) == 2){
                edges.push_back({root,it2});
                son = it2;
                break;
            }
        }
        dfs(son,it);
    }

}

void solve(int n, int subtask_id) {

    vector<int> nodes;

    for(int i = 0;i < n;i++){
        nodes.push_back(i);
    }

    dfs(0,nodes);


    for(int i = 0;i < (int)edges.size();i++){
        printf("%d %d\n",edges[i].first,edges[i].second);
    }

    answer(edges);
}
