#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int W[1000005];
vector<int> G[1000005];

void dfs(int nod,int tata){
    W[nod] = 1;
    for(auto it:G[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        W[nod] += W[it];
    }
}

int main(){

    scanf("%d",&N);

    for(int i = 1;i < N;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    dfs(1,0);

    for(int i = 2;i <= N;i++){
        if(N % i == 0){
            int num = 0,target = N / i;
            for(int j = 1;j <= N;j++){
                num  += (W[j] % target == 0);
            }
            if(num >= i){
                printf("%d ",i - 1);
            }
        }
    }

    return 0;
}
