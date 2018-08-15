#include <iostream>

using namespace std;
long long S[1805][605];
long long N,M,K;
long long adun(long long a,long long b){
   a += b;
   if(a >= M){
      a -= M;
   }
   return a;
}
long long mult(long long a,long long b){
   long long rez = 0;
   while(b){
      if(b & 1){
         rez = adun(rez,a);
      }
      b >>= 1;
      a = adun(a,a);
   }
   return rez;
}
int main() {
    cin >> N >> K >> M;
    for(int i = 1;i <= 3 * K;i++){
       for(int j = 1;j <= i;j++){
          S[i][j] = mult(i,adun(S[i - 1][j - 1],1));
       }
    }
    if(3 * K <= N){
        long long rez = 0;
        long long a = N + 3 * K + 1;
        long long b = N - 3 * K;
        if(b % 2 == 0){
           b /= 2;
        }
        else{
           a /= 2;
        }
        rez = mult(a,b);
        for(int i = 1;i <= 3 * K;i++){
          rez = adun(rez,S[i][min(i * 1LL,K)]);
        }
        cout << rez;
    }
    else{
        long long rez = 0;
        for(int i = 1;i <= N;i++){
          rez = adun(rez,S[i][min(i * 1LL,K)]);
        }
        cout << rez;
    }
    return 0;
}
