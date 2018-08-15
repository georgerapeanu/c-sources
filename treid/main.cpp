#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("treid.in","r");
FILE *g = fopen("treid.out","w");
int V[205][205];
int ROT[205][205];
int N,M;
int A[205][205];
int B[205][205];
int C[205][205];
int tmp[205];
int S[205];
int solve(){
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            ROT[M - j + 1][i] = V[i][j];
        }
    }
    swap(N,M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            V[i][j] = ROT[i][j];
        }
    }
    for(int i = 0;i <= N + 1 || i <= M + 1;i++){
        for(int j = 0;j <= N + 1 || j <= M + 1;j++){
            A[i][j] = B[i][j] = C[i][j] = - (1 << 28);
        }
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            tmp[j] = 0;
        }
        for(int j = i;j <= N;j++){
            for(int k = 1;k <= M;k++){
                tmp[k] += V[j][k];
                S[k] = tmp[k] + S[k - 1];
            }
            int ind = 0;
            for(int k = 1;k <= M;k++){
                A[i][j] = max(A[i][j],S[k] - S[ind]);
                B[j][k] = max(B[j][k],S[k] - S[ind]);
                if(S[k] < S[ind]){
                    ind = k;
                }
            }
            ind = M;
            for(int k = M;k;k--){
                if(S[k] > S[ind])
                {
                    ind = k;
                }
                C[j][k] = max(C[j][k],S[ind] - S[k - 1]);
            }
        }
    }
    for(int l = 1;l <= N;l++){
        for(int i = 1;i <= N - l;i++){
            int j = i + l;
            A[i][j] = max(A[i][j],max(A[i][j - 1],A[i + 1][j]));
        }
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            B[i][j] = max(B[i][j],max(B[i][j - 1],B[i - 1][j]));
        }
        for(int j = M;j;j--){
            C[i][j] = max(C[i][j],max(C[i][j + 1],C[i - 1][j]));
        }
    }
    int rez = - (1 << 28);
    for(int i = 1;i <= N;i++){
        for(int j = i;j <= N;j++){
            rez = max(rez,A[1][i - 1] + A[i][j] + A[j + 1][N]);
        }
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            rez = max(rez,A[i + 1][N] + B[i][j] + C[i][j + 1]);
        }
    }
    return rez;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            fscanf(f,"%d",&V[i][j]);
        }
    }
    int rez = -(1 << 30);
    for(int i = 1;i <= 4;i++){
        rez = max(rez,solve());
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
