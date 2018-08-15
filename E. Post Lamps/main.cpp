#include <cstdio>
#include <algorithm>

using namespace std;

int N,M,K;
bool marked[1000005];
int left[1000005];
int cost[1000005];

int Try(int power){
    int ans = 0;
    int poz = 0;
    while(1){
        ans++;
        if(poz + power >= N){
            return ans;
        }
        if(left[poz + power] == poz){
            return -1;
        }
        poz = left[poz + power];
    }
}

int main(){
    scanf("%d %d %d",&N,&M,&K);
    for(int i = 1;i <= M;i++){
        int poz;
        scanf("%d",&poz);
        marked[poz] = 1;
    }
    for(int i = 1;i <= K;i++){
        scanf("%d",&cost[i]);
    }

    if(marked[0]){
        printf("-1");
        return 0;
    }

    for(int i = 1;i <= N;i++){
        left[i] = (marked[i] ? left[i - 1]:i);
    }

    long long best = 1LL << 60;

    for(int i = 1;i <= K;i++){
        int ans = Try(i);
        if(ans != -1){
            best = min(best,1LL * ans * cost[i]);
        }
    }

    if(best != 1LL << 60){
        printf("%I64d",best);
    }
    else{
        printf("-1");
    }

    return 0;
}
