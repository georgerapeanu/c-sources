#include <iostream>

using namespace std;
int nrbits(int x){
    int rez = 0;
    while(x){
        rez += (x & 1);
        x >>= 1;
    }
    return rez;
}
int op[1035];
string N;
int K;
int fr[1005];
int C[1005][1005];
const int MOD = (1e9) + 7;
int main()
{
    op[1] = 0;
    for(int i = 2;i <= 1000;i++){
        op[i] = 1 + op[nrbits(i)];
    }
    for(int i = 0;i <= 1000;i++){
        C[i][0] = C[i][i] = 1;
        for(int j = 1;j < i;j++){
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if(C[i][j] >= MOD){
                C[i][j] -= MOD;
            }
        }
    }
    cin >> N >> K;
    N = " " + N;
    int biti = 0;
    for(int i = 1;i < (int)N.size();i++){
        if(N[i] == '1'){
            for(int j = biti;j <= 1000;j++){
                fr[j] += C[(int)N.size() - 1 - i][j - biti];
                if(fr[j] >= MOD){
                    fr[j] -= MOD;
                }
            }
            biti++;
        }
    }
    if(K == 0){
        cout << 1;
        return 0;
    }
    int rez = 0;
    fr[biti]++;
    for(int i = 1;i <= 1000;i++){
        if(op[i] == K - 1){
            rez = rez + fr[i];
            if(rez >= MOD){
                rez -= MOD;
            }
        }
    }
    cout << (rez - (K == 1) + MOD ) % MOD;
    return 0;
}
