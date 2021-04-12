#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("biconexe.in","r");
FILE *g = fopen("biconexe.out","w");

const int NMAX = 1e5;
const int MMAX = 2e5;

int n,m;
vector<int> graph[NMAX + 5];

int last_id;
int id[NMAX + 5];
int low[NMAX + 5];

pair<int,int> dfs_stack[MMAX + 5];
int len_stack;

vector<vector<int>> components;

void dfs(int nod,int tata){
    id[nod] = low[nod] = ++last_id;

    for(auto it:graph[nod]){
        if(it == tata){
            low[nod] = min(low[nod],id[tata]);
            continue;
        }

        if(id[it] == 0){
            dfs_stack[++len_stack] = {nod,it};
            dfs(it,nod);
            low[nod] = min(low[nod],low[it]);

            if(low[it] == id[nod]){
                vector<int> component;

                while(dfs_stack[len_stack] != make_pair(nod,it)){
                    component.push_back(dfs_stack[len_stack].first);
                    component.push_back(dfs_stack[len_stack].second);
                    len_stack--;
                }
                component.push_back(dfs_stack[len_stack].first);
                component.push_back(dfs_stack[len_stack].second);
                len_stack--;

                sort(component.begin(),component.end());
                component.resize(unique(component.begin(),component.end()) - component.begin());

                components.push_back(component);
            }
        }
        if(id[it] < id[nod]){
            low[nod] = min(low[nod],id[it]);
        }
    }
}

int main(){

    freopen("biconex.in","r",stdin);
    freopen("biconex.out","w",stdout);

    scanf("%d %d",&n,&m);

    while(m--){
        int a,b;
        scanf("%d %d",&a,&b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i = 1;i <= n;i++){
        if(id[i] == 0){
            dfs(i,0);
        }
    }

    printf("%d\n",(int)components.size());

    for(auto it:components){
        for(auto it2:it){
            printf("%d ",it2);
        }
        printf("\n");
    }

    return 0;
}
