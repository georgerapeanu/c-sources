#include <iostream>

using namespace std;

int N,M;

int C[1005];
int A[1005];

int main(){

    cin >> N >> M;

    for(int i = 1;i <= N;i++){
        cin >> C[i];
    }

    for(int j = 1;j <= M;j++){
        cin >> A[j];
    }

    int st = 1,ans = 0;

    for(int i = 1;i <= N;i++){
        ans += (C[i] <= A[st]);
        st += (C[i] <= A[st]);
    }

    cout << ans;

    return 0;
}
