#include <iostream>
#define LIM (2e18)
using namespace std;
long long len[100005],N,K,T;
string s = "What are you doing at the end of the world? Are you busy? Will you save us?";
string a = "What are you doing while sending \"";
string b = "\"? Are you busy? Will you send \"";
string c ="\"?";
char solve(long long N,long long K){
    if(len[N] < K){
        return '.';
    }
    if(N == 0){
        return s[K - 1];
    }
    if(K <= (int)a.size()){
        return a[K - 1];
    }
    K -= (int)a.size();
    if(K <= len[N-1]){
        return solve(N - 1,K);
    }
    K -= len[N-1];
    if(K <= (int)b.size()){
        return b[K - 1];
    }
    K -= (int)b.size();
     if(K <= len[N-1]){
        return solve(N - 1,K);
    }
    K -= len[N - 1];
    return c[K - 1];
}
int main(){
    len[0] = 75;
    for(int i = 1;i <= 100000;i++){
        if((LIM - 68) / 2 >= len[i - 1]){
            len[i] = 2 * len[i-1] + 68;
        }
        else
        {
            len[i] = LIM;
        }
    }
    cin >> T;
    while(T--){
        cin >> N >> K;
        cout << solve(N,K);
    }
    return 0;
}
