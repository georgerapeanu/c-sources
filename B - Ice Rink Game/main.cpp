#include <iostream>

using namespace std;
long long NMAX,NMIN;
int K;
int A[100005];
long long eval(long long N){
    for(int i = 1;i <= K;i++){
        N = (N / A[i]) * A[i];
    }
    return N;
}
int main()
{
    cin >> K;
    for(int i = 1;i <= K;i++){
        cin >> A[i];
    }
    long long st = 0,dr = 1e18;
    while(dr - st > 1){
        long long mid = (st + dr) / 2;
        if(eval(mid) >= 2){
            dr = mid;
        }
        else {
            st = mid;
        }
    }
    if(eval(dr) != 2){
        cout << -1;
        return 0;
    }
    cout << dr << " ";
    st = 0,dr = 1e18;
    while(dr - st > 1){
        long long mid = (st + dr) / 2;
        if(eval(mid) <= 2){
            st = mid;
        }
        else {
            dr = mid;
        }
    }
    cout << st << " ";
    return 0;
}
