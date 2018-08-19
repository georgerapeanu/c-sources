#include <iostream>
using namespace std;
int N,K;
int V[100006];
bool U[1 << 4];
int main(){
    cin >> N >> K;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= K;j++){
            int tmp;
            cin >> tmp;
            V[i] = (V[i] << 1) + tmp;
        }
        for(int mask2 = ((1 << K) - 1) ^ V[i];mask2;mask2 = (mask2 - 1) & (((1 << K) - 1) ^ V[i])){
            if(U[mask2]){
                cout << "YES";
                return 0;
            }
        }
        if(V[i] == 0){
            cout << "YES";
            return 0;
        }
        U[V[i]] = 1;
    }
    cout << "NO";
    return 0;
}
