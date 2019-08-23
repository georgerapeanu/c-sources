#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int LGMAX = 62;

int n;

vector<int> graph[NMAX + LGMAX + 5];
int viz[NMAX + LGMAX + 5];

void dfs(int nod,int &ans){
    if(viz[nod] > 2 * ans + 4){
        return ;
    }
    for(auto it:graph[nod]){
        if(viz[it] == 0){
            viz[it] = 1 + viz[nod];
            dfs(it,ans);
        }
        else{
            if((viz[nod] - viz[it] + 1) / 2 > 2){
                ans = min(ans,(viz[nod] - viz[it] + 1) / 2);
            }
        }
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        long long a;
        scanf("%lld",&a);

        for(int j = 0;j <= LGMAX;j++){
            if(((a >> j) & 1) == 0){
                continue;
            }
            graph[i].push_back(j + NMAX + 1);
            graph[j + NMAX + 1].push_back(i);
        }
    }

    int ans = 1 << 26;

    for(int i = 0 + NMAX + 1;i <= LGMAX + NMAX + 1;i++){
        if((int)graph[i].size() >= 3){
            printf("3\n");
            return 0;
        }
    }

    for(int i = 0 + NMAX + 1;i <= LGMAX + NMAX + 1;i++){
        memset(viz,0,sizeof(viz));
        viz[i] = 1;
        dfs(i,ans);
    }

    printf("%d\n",(ans == (1 << 26) ? -1:ans));


    return 0;
}
