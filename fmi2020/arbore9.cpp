#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("arbore9.in","r");
FILE *g = fopen("arbore9.out","w");

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;


    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    if(buff[ind] == '-'){
        sgn *= -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans * sgn;
}

struct edge_t{
    int u,v;
    int a,b;

    int other(int nod){
        return u ^ v ^ nod;
    }
};

const int NMAX = 1e5;
edge_t edges[2 * NMAX + 5];
int n;
vector<int> graph[NMAX + 5];

long long dp[NMAX + 5][2];

void predfs(int nod,int tata){
    dp[nod][0] = 0;
    dp[nod][1] = 0;

    long long best_upgrade = 0;

    for(auto edge:graph[nod]){
        int it = edges[edge].other(nod);
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        dp[nod][0] += max(dp[it][0] + edges[edge].b,0LL);
        best_upgrade = max(best_upgrade,dp[it][1] + edges[edge].a - max(dp[it][0] + edges[edge].b,0LL));
    }

    dp[nod][1] = dp[nod][0] + best_upgrade;
}

long long ans[NMAX + 5]; 

void dfs(int nod,int tata){
    long long local_dp[2] = {dp[nod][0],dp[nod][1]};

    pair<long long,int> upgrade1,upgrade2;
    upgrade1 = upgrade2 = {0LL,-1};

    dp[nod][0] = dp[nod][1] = 0;

    for(auto edge:graph[nod]){
        int it = edges[edge].other(nod);
        dp[nod][0] += max(dp[it][0] + edges[edge].b,0LL);
        pair<long long,int> local_upgrade = {dp[it][1] + edges[edge].a - max(dp[it][0] + edges[edge].b,0LL),it};
        if(local_upgrade > upgrade1){
            upgrade2 = upgrade1;
            upgrade1 = local_upgrade;
        }
        else if(local_upgrade > upgrade2){
            upgrade2 = local_upgrade;
        }
    }

    dp[nod][1] = dp[nod][0] + upgrade1.first;
    ans[nod] = dp[nod][1];

    for(auto edge:graph[nod]){
        int it = edges[edge].other(nod);
        if(it == tata){
            continue;
        }
        dp[nod][0] -= max(dp[it][0] + edges[edge].b,0LL);
        if(upgrade1.second != it){
            dp[nod][1] = dp[nod][0] + upgrade1.first;
        }
        else{
            dp[nod][1] = dp[nod][0] + upgrade2.first;
        }
        dfs(it,nod);
        dp[nod][0] += max(dp[it][0] + edges[edge].b,0LL);
        dp[nod][1] = dp[nod][0] + upgrade1.first;

    }

    dp[nod][0] = local_dp[0];
    dp[nod][1] = local_dp[1];
}

int main(){

    n = i32();

    for(int i = 1;i < n;i++){
        edges[2 * i - 1].u = i32();
        edges[2 * i - 1].v = i32();
        edges[2 * i - 1].a = i32();
        edges[2 * i - 1].b = i32();
        edges[2 * i] = edges[2 * i - 1];
        swap(edges[2 * i].a,edges[2 * i].b);
        swap(edges[2 * i].u,edges[2 * i].v);
        graph[edges[2 * i - 1].u].push_back(2 * i - 1);
        graph[edges[2 * i - 1].v].push_back(2 * i);
    }

    predfs(1,0);
    dfs(1,0);

    for(int i = 1;i <= n;i++){
        fprintf(g,"%lld ",ans[i]);
    }
    
    fclose(f);
    fclose(g);

    return 0;
}
