#include "chameleon.h"
#include <vector>
#include <cstdio>
#include <cassert>

using namespace std;

vector<int> graph[1005];
vector<int> groups[2];
bool viz[1005];

void dfs(int nod,int lvl){
    
    viz[nod] = 1;
    groups[lvl].push_back(nod);

    for(auto it:graph[nod]){
        if(viz[it]){
            continue;;
        }
        dfs(it,lvl ^ 1);
    }
}

void make_groups(int pas){
    for(int i = 1;i <= pas;i++){
        viz[i] = false;
    }
    groups[0].clear();
    groups[1].clear();
    for(int i = 1;i <= pas;i++){
        if(viz[i] == 0){
            dfs(i,0);
        }
    }
}

int ans[1005];
int lover[1005];

vector<int> reunite(vector<int> a,vector<int> b){
    vector<int> ans;
    for(auto it:a)ans.push_back(it);
    for(auto it:b)ans.push_back(it);
    return ans;
}
vector<int> prefix(vector<int> a,int ind){
    vector<int> ans;
    for(int i = 0;i <= ind;i++){
        ans.push_back(a[i]);
    }
    return ans;
}
vector<int> del(vector<int> a,int val){
    vector<int> ans;
    for(auto it:a){
        if(it == val){
            continue;
        }
        ans.push_back(it);
    }
    return ans;
}

int my_query(const vector<int> &v){
    return Query(v);
}

void Solve(int n) {
    
    for(int i = 1;i <= 2 * n;i++){
        make_groups(i - 1);

        for(int k = 0;k < 2;k++){
            while(my_query(reunite({i},groups[k])) != reunite({i},groups[k]).size()){
                int st = -1,dr = (int)groups[k].size() - 1;

                while(dr - st > 1){
                    int mid = (st + dr) / 2;
                    if(my_query(reunite({i},prefix(groups[k],mid))) == mid + 2){
                        st = mid;
                    }
                    else{
                        dr = mid;
                    }
                }

                graph[i].push_back(groups[k][dr]);
                graph[groups[k][dr]].push_back(i);

                groups[k] = del(groups[k],groups[k][dr]);
            }
        }
    }

    for(int i = 1;i <= 2 * n;i++){
        if(graph[i].size() == 1){
            continue;
        }
        int loves = 0;
        for(loves = 0;loves < (int)graph[i].size();loves++){
            if(graph[i][(loves + 1) % 3] == graph[i][(loves + 2) % 3]){
                loves = (loves + 1) % 3;
                break;
            }
            if(my_query({i,graph[i][(loves + 1) % 3],graph[i][(loves + 2) % 3]}) == 1){
                break;
            }
        }
        lover[i] = graph[i][loves];
    }

    for(int i = 1;i <= 2 * n;i++){
        if(ans[i] == 0){
            for(auto it:graph[i]){
                if(lover[i] == it || lover[it] == i){
                    continue;
                }
                ans[i] = it;
                ans[it] = i;
                Answer(i,it);
                break;
            }
        }
    }
}
