#include <iostream>
using namespace std;
int A[100005];
int B[100005];
int M;
int N;
int cnt[100005];
const int MOD = (1e9) + 7;
int adun(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}
int mult(int a,int b){
    return 1LL * a * b % MOD;
}
int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }
    return p;
}
int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin >> N >> M;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
        cnt[i] += (A[i] == 0);
    }
    for(int i = 1;i <= N;i++){
        cin >> B[i];
        cnt[i] += (B[i] == 0);
    }
    for(int i = N;i;i--){
        cnt[i] += cnt[i + 1];
    }
    int prefProb = 1,rez = 0;
    for(int i = 1;i <= N;i++){
        if(A[i] && B[i]){
            if(A[i] != B[i]){
                if(A[i] > B[i]){
                    rez = adun(rez,prefProb);
                }
                break;
            }
        }
        else if(A[i] && !B[i]){
            rez = adun(rez,mult(mult(prefProb,A[i] - 1),lgpow(M,MOD - 2)));
            prefProb = mult(prefProb,lgpow(M,MOD - 2));
        }
        else if(!A[i] && B[i]){
            rez = adun(rez,mult(mult(prefProb,M - B[i]),lgpow(M,MOD - 2)));
            prefProb = mult(prefProb,lgpow(M,MOD - 2));
        }
        else{
            rez = adun(rez,mult(prefProb,mult(M - 1,lgpow(2 * M,MOD - 2))));
            prefProb = mult(prefProb,lgpow(M,MOD - 2));
        }
    }
    cout  << rez;
    return 0;
}
