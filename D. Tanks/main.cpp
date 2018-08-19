#include <iostream>
#include <vector>
using namespace std;
int dp[5005][5005];
int N,K;
int V;
int S;
int A[5005];
int main(){
    cin >> N >> K >> V;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
        S += A[i];
    }
    if(S < V){
        cout << "NO";
        return 0;
    }
    dp[0][0] = -1;
    for(int i = 1;i <= N;i++){
        for(int j = 0;j < K;j++){
            if(dp[i - 1][(j + K - (A[i] % K)) % K]){
                dp[i][j] = 2;
            }
            else if(dp[i - 1][j]){
                dp[i][j] = 1;
            }
        }
    }
    vector<int> U;
    int x = N,y = V % K;
    if(!dp[x][y]){
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    while(x || y){
        if(dp[x][y] == 2){
            U.push_back(x);
            y = (y + K - (A[x] % K)) % K;
        }
        x--;
    }
    if(U.empty()){
        int colector = 1;
        for(int i = 1;i <= N;i++){
            if(A[i] && i != colector){
                cout << A[i] / K + (A[i] % K != 0)<< " " << i << " " << colector << "\n";
                A[colector] += (A[i] / K) * K;
            }
        }
        if(!V){
            return 0;
        }
        cout << V / K << " " << colector << " " << 2 << "\n";
        return 0;
    }
    for(int i = 1;i < (int)U.size();i++){
        if(!A[U[i]]){
            continue;
        }
        A[U[0]] += A[U[i]];
        cout << ((A[U[i]] / K) + (A[U[i]] % K != 0)) << " " << U[i] << " " << U[0] << "\n";
        A[U[i]] = 0;
    }
    if(A[U[0]] > V){
        cout << (A[U[0]] - V) / K << " " << U[0] << " " << (U[0] == 1 ? 2:1) << "\n";
    }
    else if(A[U[0]] < V){
        int colector = (U[0] == 1 ? 2:1);
        for(int i = 1;i <= N && A[U[0]] < V;i++){
            if(A[i] && i != U[0] && i != colector){
                cout << A[i] / K + (A[i] % K != 0)<< " " << i << " " << colector << "\n";
                A[colector] += (A[i] / K) * K;
            }
        }
        cout << (V - A[U[0]]) / K << " " << colector << " " << U[0] << "\n";
    }
    return 0;
}
