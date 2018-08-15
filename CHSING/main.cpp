#include <iostream>
using namespace std;
long long  T;
long long  N;
long long  A[100005];
long long dp[100005][8];
long long  ant[100005][8];
long long  eval(long long  st,long long  dr,long long  conf){
    long long  rez = 0;
    for(long long  i = st;i <= dr;i++){
        rez += A[i] * (((conf >> (i - st)) & 1) ? -1:1);
    }
    return rez;
}
bool valid(long long  st,long long  dr,long long  conf){
    for(long long  i = st;i < dr;i++){
        long long  a = A[i] * (((conf >> (i - st)) & 1) ? -1:1);
        long long  b = A[i + 1] * (((conf >> (i + 1 - st)) & 1) ? -1:1);
        if(a + b <= 0){
            return 0;
        }
    }
    return eval(st,dr,conf) > 0;
}
int  main(){
    cin >> T;
    while(T--){
        cin >> N;
        for(long long  i = 1;i <= N;i++){
            cin >> A[i];
        }
        if(N == 2){
            if(A[1] < A[2]){
                cout << -A[1] << " " << A[2] << "\n";
            }
            else if(A[1] == A[2]){
                cout << A[1] << " " << A[2] << "\n";
            }
            else{
                cout << A[1] << " " << -A[2] << "\n";
            }
            continue;
        }
        else{
            for(long long  conf = 0;conf < 8;conf++){
                dp[3][conf] = eval(1,3,conf);
                if(!valid(1,3,conf)){
                    dp[3][conf] = 1LL << 60;
                }
            }
            for(long long  i = 4;i <= N;i++){
                for(long long  conf = 0;conf < 8;conf++){
                    dp[i][conf] = 1LL << 60;
                    if(valid(i - 2,i,conf)){
                        if(dp[i - 1][((conf << 1) & 7)] < dp[i - 1][((conf << 1) & 7) + 1]){
                            dp[i][conf] = dp[i - 1][((conf << 1) & 7)] + (((conf >> 2) & 1) ? -A[i]:A[i]);
                            ant[i][conf] = ((conf << 1) & 7);
                        }
                        else{
                            dp[i][conf] = dp[i - 1][((conf << 1) & 7) + 1] + (((conf >> 2) & 1) ? -A[i]:A[i]);
                            ant[i][conf] = ((conf << 1) & 7) + 1;
                        }
                    }
                }
            }
            long long  ind = 0;
            for(long long  i = 0;i < 8;i++){
                if(dp[N][i] < dp[N][ind]){
                    ind = i;
                }
            }
            long long  wh = N;
            while(wh > 3){
                A[wh] *= (((ind >> 2) & 1) ? -1:1);
                ind = ant[wh][ind];
                wh--;
            }
            A[1] *= ((ind & 1) ? -1:1);
            A[2] *= ((ind & 2) ? -1:1);
            A[3] *= ((ind & 4) ? -1:1);
            for(long long  i = 1;i <= N;i++){
                cout << A[i] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
