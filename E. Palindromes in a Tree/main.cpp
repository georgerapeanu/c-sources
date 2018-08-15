#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
map<int,int> nodes[200005];
vector<int> G[200005];
char S[200005];
int N;
long long R[200005];
void predfs(int nod,int tata){
    for(auto it:G[nod]){
        if(it != tata){
            predfs(it,nod);
            for(auto it2:nodes[it]){
                nodes[nod][it2.first ^(1 << (S[nod] - 'a'))] += it2.second;
            }
        }
    }
    nodes[nod][1 << (S[nod] - 'a')]++;
}
void dfs(int nod,int tata){
    if(tata){
        for(auto it:nodes[nod]){
            nodes[tata][it.first] -= it.second;
            nodes[nod][it.first] += nodes[tata][it.first];
        }
    }
    nodes[nod].clear();
    nodes[nod][1 << (S[nod] - 'a')]++;
    R[nod] = 1;
    for(auto it:G[nod]){
        for(auto it2:nodes[it]){
            R[nod] += 1LL * nodes[nod][it2.first] * it2.second;
            for(int i = 0;i < 26;i++){
                R[nod] += 1LL * it2.second * nodes[nod][it2.first ^ (1 << i)];
            }
            nodes[nod][it2.first ^ (1 << (S[nod] - 'a'))] += it2.second;
        }
    }
    for(auto it:G[nod]){
        if(it != tata){
            dfs(it,nod);
        }
    }
    if(tata){
        for(auto it:nodes[nod]){
            nodes[tata][it.first] += it.second;
            nodes[nod][it.first] -= nodes[tata][it.first];
        }
    }
}
int main()
{
    scanf("%d\n",&N);
    for(int i = 1;i < N;i++){
        int x,y;
        scanf("%d %d\n",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    fgets(S + 1,200005,stdin);
    predfs(1,0);
    dfs(1,0);
    for(int i = 1;i <= N;i++){
        printf("%lld ",R[i]);
    }
    return 0;
}
