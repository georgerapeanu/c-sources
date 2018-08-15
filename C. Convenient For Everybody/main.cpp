#include <cstdio>
#include <algorithm>
using namespace std;
int N;
int S,F;
int V[100005];
int partial[100005],ans,where;
int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        scanf("%d",&V[i]);
    }
    scanf("%d %d",&S,&F);
    for(int i = 1;i <= N;i++){if(S <= F){partial[S] += V[i];partial[F] -= V[i];}
        else{partial[S] += V[i];partial[1] += V[i];partial[F] -= V[i];}
        S--;if(S == 0) S = N;
        F--;if(F == 0) F = N;
    }
    for(int i = 1;i <= N;i++){
        partial[i] += partial[i - 1];
        if(ans < partial[i]){
            ans = partial[i];
            where = i;
        }
    }
    printf("%d",where);
    return 0;
}
