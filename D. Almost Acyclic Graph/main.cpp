#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
multiset<int> G[505];
int st[505],len;
int N,M;
vector<int> cycle;
bool found;
bool inst[505];
bool viz[505];
void dfs(int nod){
    st[++len] = nod;
    inst[nod] = 1;
    viz[nod] = 1;
    for(auto it:G[nod]){
        if(!viz[it]){
            dfs(it);
            if(found){
                return ;
            }
        }
        else if(inst[it]){
            found = 1;
            while(st[len] != it){
                cycle.push_back(st[len]);
                len--;
            }
            cycle.push_back(it);
            return ;
        }
    }
    len--;
    inst[nod] = 0;
}
void dfs2(int nod){
    st[++len] = nod;
    inst[nod] = 1;
    viz[nod] = 1;
    for(auto it:G[nod]){
        if(!viz[it]){
            dfs2(it);
            if(!found){
                return ;
            }
        }
        else if(inst[it]){
            found = 0;
            return ;
        }
    }
    len--;
    inst[nod] = 0;
}
int main()
{
    scanf("%d %d",&N,&M);
    while(M--){
        int x,y;
        scanf("%d %d",&x,&y);
        G[x].insert(y);
    }
    for(int i = 1;i <= N;i++){
        if(!viz[i]){
            dfs(i);
            if(found){
                break;
            }
        }
    }
    reverse(cycle.begin(),cycle.end());
    if(cycle.empty()){
        puts("YES");
        return 0;
    }
    for(int i = 0;i < cycle.size();i++){
        int x = cycle[i],y = cycle[(i + 1) % cycle.size()];
        G[x].erase(G[x].find(y));
        memset(viz,0,sizeof(viz));
        found = 1;
        for(int i = 1;i <= N;i++){
            if(!viz[i]){
                len = 0;
                dfs2(i);
                if(!found){
                    break;
                }
            }
        }
        if(found){
            puts("YES");
            return 0;
        }
        G[x].insert(y);
    }
    puts("NO");
    return 0;
}
