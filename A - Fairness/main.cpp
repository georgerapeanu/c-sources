#include <iostream>
#include <algorithm>

using namespace std;

const long long LIM = 1e18;

long long V[4];
long long NV[4];

long long K;

int main(){

    cin >> V[1] >> V[2] >> V[3] >> K;
    long long ans = V[1] - V[2];
    if(K % 2){
        ans *= -1;
    }
    if(abs(ans) > LIM){
        cout << "Unfair";
    }
    else{
        cout << ans;
    }
    return 0;
}
