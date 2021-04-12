#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n,m;
vector<int> graph[2 * NMAX + 5];
vector<int> graph2[2 * NMAX + 5];
int gr2[2 * NMAX + 5];
int state[2 * NMAX + 5];
int last_ctc;
int ctc[2 * NMAX + 5];
vector<vector<int>> components;

int low[2 * NMAX + 5];
int id[2 * NMAX + 5];
int last_id;

int dfs_stack[2 * NMAX + 5];
bool in_stack[2 * NMAX + 5];
int len_stack;

void dfs(int nod){
    dfs_stack[++len_stack] = nod;
    in_stack[nod] = true;
    id[nod] = low[nod] = ++len_stack;

    for(auto it:graph[nod]){
        if(id[it] == 0){
            dfs(it);
        }
        if(in_stack[it]){
            low[nod] = min(low[nod],low[it]); 
        }
    }

    if(low[nod] == id[nod]){
        last_ctc++;
        vector<int> component;
        while(dfs_stack[len_stack] != nod){
            ctc[dfs_stack[len_stack]] = last_ctc;
            in_stack[dfs_stack[len_stack]] = false;
            component.push_back(dfs_stack[len_stack]);
            len_stack--;
        }
        ctc[dfs_stack[len_stack]] = last_ctc;
        in_stack[dfs_stack[len_stack]] = false;
        component.push_back(dfs_stack[len_stack]);
        len_stack--;

        components.push_back(component);
    }
}

int main(){

    components.resize(1);

    freopen("2sat.in","r",stdin);
    freopen("2sat.out","w",stdout);

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int a,b;
        scanf("%d %d",&a,&b);

        a += n + 1;
        b += n + 1;

        graph[2 * (n + 1) - a].push_back(b);
        graph[2 * (n + 1) - b].push_back(a);
    }

    for(int i = 1;i <= n + 1 + n;i++){
        if(i == n + 1){
            continue;
        }
        if(id[i] == 0){
            dfs(i);
        }
    }

    for(int i = 1;i <= n;i++){
        if(ctc[i] == ctc[2 * (n + 1) - i]){
            printf("-1");
            return 0;
        }
    }

    for(int i = 1;i <= (n + 1) + n;i++){
        for(auto it:graph[i]){
            if(ctc[i] != ctc[it]){
                graph2[ctc[i]].push_back(ctc[it]);
                gr2[ctc[it]]++;
            }
        }
    }

    vector<int> topological;

    for(int i = 1;i <= last_ctc;i++){
        if(gr2[i] == 0){
            topological.push_back(i);
        }
    }

    for(int i = 0;i < (int)topological.size();i++){
        for(auto it:graph2[topological[i]]){
            gr2[it]--;
            if(gr2[it] == 0){
                topological.push_back(it);
            }
        }
    }

    for(auto it:topological){
        int current_state = state[it];
        for(auto it2:components[it]){
            if(state[ctc[2 * (n + 1) - it2]] != 0){
                if(current_state && state[ctc[2 * (n + 1) - it2]] == current_state){
                    printf("-1");
                    return 0;
                }
                current_state = 3 - state[ctc[2 * (n + 1) - it2]];
            }
        }
        if(current_state == 0){
            current_state = 1;
        }
        state[it] = current_state;
        if(state[it] == 2){
            for(auto it2:graph2[it]){
                if(state[it2] == 1){
                    printf("-1");
                    return 0;
                }
                state[it2] = 2;
            }
        }
    }

    for(int i = n + 1 + 1;i <= n + 1 + n;i++){
        printf("%d ",(state[ctc[i]] == 2));
    }

    return 0;
}
