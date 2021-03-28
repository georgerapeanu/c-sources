#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e3;
const int MMAX = 3e3;

struct edge_t{
    int x,y;

    int other(int u){
        return u ^ x ^ y;
    }
};

int n,m;
vector<int> graph[NMAX + 5];
int where[NMAX + 5];
int gr[NMAX + 5]; 
int cnt_used;
bool used[MMAX + 5];
edge_t edges[MMAX + 5];

vector<int> path;

void reset(){
    cnt_used = 0;
    path.clear();
    for(int i = 1;i <= m;i++){
        used[i] = false;
    }
    for(int i = 1;i <= n;i++){
        where[i] = (int)graph[i].size() - 1;
    }
}

void answer(vector<int> path){
    //reverse(path.begin(),path.end());

    printf("%d\n",(int)path.size());

    for(auto it:path){
        printf("%d ",it);
    }

    exit(0);
}

void dfs(int nod){
    while(where[nod] >= 0){
        while(where[nod] >= 0 && used[graph[nod][where[nod]]]){
            where[nod]--;
        }

        if(where[nod] >= 0){
            used[graph[nod][where[nod]]] = true;
            cnt_used++;
            dfs(edges[graph[nod][where[nod]]].other(nod));
        }
    }
    path.push_back(nod);
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        scanf("%d %d",&edges[i].x,&edges[i].y);
        graph[edges[i].x].push_back(i);
        graph[edges[i].y].push_back(i);
        gr[edges[i].x]++;
        gr[edges[i].y]++;
    }

    vector<int> odd;

    for(int i = 1;i <= n;i++){
        if(gr[i] & 1){
            odd.push_back(i);
        }
    }

    reset();
    if((int)odd.size() <= 2){
        dfs(odd.empty() ? 1:odd[0]);
        answer(path);
    }

    for(int i = 1;i <= n;i++){
        vector<int> local_odd;
        for(auto it:graph[i]){
            if(gr[edges[it].other(i)] % 2 == 1){
                local_odd.push_back(it);
            }
        }
        reset();
        vector<int> local_path;
        if((gr[i] - ((int)local_odd.size())) % 2 == 1){
            if((int)odd.size() - (int)local_odd.size() + (gr[i] % 2 == 0) <= 2){
                for(auto it:local_odd){
                    local_path.push_back(edges[it].other(i));
                    local_path.push_back(i);
                    used[it] = true;
                    cnt_used++;
                }
                dfs(i);
            }
        }else if((int)local_odd.size() == 0){
            if((int)odd.size() == 0){
                local_path.push_back(edges[graph[i][0]].other(i));
                local_path.push_back(i);
                used[graph[i][0]] = true;
                cnt_used++;
                dfs(i);
            }
        }else{
            if((int)odd.size() - ((int)local_odd.size() - 1) + (gr[i] % 2 == 0) <= 2){
                for(auto who:local_odd){
                    reset();
                    local_path.clear();
                    for(auto it:local_odd){
                        if(it == who){
                            continue;
                        }
                        local_path.push_back(edges[it].other(i));
                        local_path.push_back(i);
                        used[it] = true;
                        cnt_used++;
                    }
                    dfs(i);
                    if(cnt_used == m){
                        break; 
                    }
                }
            }
        }

        vector<int>real_path;
        if(path.size()){
            for(auto it:path){
                real_path.push_back(it);
            }
            real_path.push_back(-1);
            for(auto it:local_path){
                real_path.push_back(it);
            }
            if(cnt_used == m){
                answer(real_path);       
            }
        }
        
    }

    printf("0\n");

    return 0;
}
