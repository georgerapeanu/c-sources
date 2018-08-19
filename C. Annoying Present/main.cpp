#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;

int N,M;
long long ans;

int main(){

    cin >> N >> M;

    long long msum = 0,Msum = 0;

    for(int i = 1;i <= N;i++){
        msum += abs(i - (N + 1) / 2);
        Msum += i - 1;
    }

    while(M--){
        int X,D;
        cin >> X >> D;
        ans = ans + 1LL * X * N + max(1LL * D * msum,1LL * D * Msum);
    }

    cout << fixed << setprecision(10) << (ans / (long double)N);

    return 0;
}
