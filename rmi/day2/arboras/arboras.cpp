#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

int n,q;
vector<int> graph[NMAX + 5];
int father[NMAX + 5];
long long dist[NMAX + 5];

long long dp[NMAX + 5];

vector<pair<long long,int> > bst[NMAX + 5];

int ans;

bool recalculate(int nod,int who){
    if(bst[nod][0].second == who){
        bst[nod][0].first = bst[who][0].first + dist[who];
    }
    else if(bst[nod][1].second == who){
        bst[nod][1].first = bst[who][1].first + dist[who];
    }
    else{
        bst[nod].push_back({bst[who][0].first + dist[who],who});
    }
    sort(bst[nod].begin(),bst[nod].end());
    reverse(bst[nod].begin(),bst[nod].end());
    while(bst[nod].size() > 2){
        bst[nod].pop_back();
    }
    dp[nod] = bst[nod][0].first + bst[nod][1].first;
    if(bst[nod][0].second != who){
        return false;
    }
    return true;
}

void dfs(int nod){
    bst[nod].clear();
    bst[nod].push_back({0,nod});
    bst[nod].push_back({0,nod});
    for(auto it:graph[nod]){
        dfs(it);
        bst[nod].push_back({bst[it][0].first + dist[it],it});
    }

    sort(bst[nod].begin(),bst[nod].end());
    reverse(bst[nod].begin(),bst[nod].end());

    while(bst[nod].size() > 2){
        bst[nod].pop_back();
    }

    dp[nod] = bst[nod][0].first + bst[nod][1].first; 
    ans = (ans + (dp[nod] % MOD)) % MOD;
}

void update(int a,int b){
    dist[a] += b;
    for(int nod = father[a],fiu = a;nod != 0;nod = father[nod],fiu = father[fiu]){
        ans = (ans - (dp[nod] % MOD)) % MOD;
        bool tmp = recalculate(nod,fiu);
        ans = (ans + (dp[nod] % MOD)) % MOD;
        ans = (ans + MOD) % MOD;
        if(tmp == false){
            break;
        }
    }
}

int main(){

    scanf("%d",&n);

    for(int i = 2;i <= n;i++){
        scanf("%d",&father[i]);
        father[i]++;
        graph[father[i]].push_back(i);
    }
    for(int i = 2;i <= n;i++){
        scanf("%lld",&dist[i]);
    }

    ans = 0;
    dfs(1);
    printf("%d\n",ans);
    int q;
    scanf("%d",&q);
    for(int i = 1;i <= q;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        a++;
        update(a,b);
        printf("%d\n",ans);
    }

    return 0;
}

