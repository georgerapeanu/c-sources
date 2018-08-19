#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;
int pd23[2][100005][2];
int N,K;
int l[105];
int r[105];
int dequeee[100005],stq,drq;
int main(){
    scanf("%d %d",&N,&K);
    for(int i = 1;i <= K;i++){
        scanf("%d %d",&l[i],&r[i]);
    }
    for(int i = 0;i <= N;i++){
        pd23[0][i][0] = 1 << 28;
        pd23[0][i][1] = 1 << 28;
    }
    pd23[0][0][0] = 0;
    for(int i = 1,la = 1;i <= K;i++,la ^= 1){
        stq = 1;drq = 0;
        for(int j = 0;j <= N;j++){
pd23[la][j][0] = pd23[!la][j][0];
            pd23[la][j][1] = (r[i] - r[i - 1] <= j ? pd23[!la][j - r[i] + r[i - 1]][1] : 1 << 28);
            while(stq <= drq && j - dequeee[stq] > r[i] - l[i]){
                stq++;
    }
            while(stq <= drq && pd23[!la][dequeee[drq]][0] > pd23[!la][j][0]){
                drq--;
            }
            dequeee[++drq] = j;
    pd23[la][j][0] = min(pd23[la][j][0],pd23[!la][dequeee[stq]][0] + 2);
            pd23[la][j][1] = min(pd23[la][j][1],pd23[!la][dequeee[stq]][0] + 1);
        }
        stq = 1;drq = 0;
            for(int j = 0;j <= N;j++){
            while(stq <= drq && j - dequeee[stq] > r[i] - r[i - 1]){
                stq++;
            }
            if(j + r[i - 1] >= l[i]){
                while(stq <= drq && pd23[!la][dequeee[drq]][1] > pd23[!la][j + r[i - 1] - l[i]][1]){
                    drq--;
            }
                dequeee[++drq] = j + r[i - 1] - l[i];
            }
            if(stq <= drq){
                pd23[la][j][0] = min(pd23[la][j][0],pd23[!la][dequeee[stq]][1] + 1);
                pd23[la][j][1] = min(pd23[la][j][1],pd23[!la][dequeee[stq]][1] + 2);
            }
        }
    }
    int tmp = min(pd23[K & 1][N][0],(N - (2 * N - r[K]) >= 0 ? pd23[K & 1][N - (2 * N - r[K])][1]:1 << 28));
    if(tmp == 1 << 28){
        printf("Hungry\n");
        return 0;
    }
    printf("Full\n%d",tmp);
    return 0;
}
