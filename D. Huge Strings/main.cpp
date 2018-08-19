#include <iostream>

using namespace std;
string S[205];
int N;
int M;
int dp[10005];
int rundp(string &s){
    int last0 = -1,last1 = -1;
    for(int i = (int)s.size() - 1;i >= 0;i--){
        if(s[i] == '0'){
            last0 = i;
        }
        else{
            last1 = i;
        }
        if(last0 != -1 && last1 != -1){
            dp[i] = dp[max(last0,last1) + 1] + 1;///plm
        }
        else{
            dp[i] = 0;
        }
    }
    return dp[0];
}
int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> S[i];
    }
    cin >> M;
    while(M--){
        int a,b;
        cin >> a >> b;
        S[++N] = S[a] + S[b];
        cout << rundp(S[N]) << "\n";
    }
    return 0;
}
