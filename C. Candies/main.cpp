#include <iostream>

using namespace std;

long long N;

long long check(long long val){
    long long sum = 0;
    long long cN = N;
    while(cN){
        sum += min(cN,val);
        cN -= min(cN,val);
        cN -= cN / 10;
    }
    return sum;
}

int main()
{
    cin >> N;
    long long st = 0,dr = N / 2 + N % 2;
    while(dr - st > 1){
        long long mid = (st + dr) / 2;
        if(check(mid) >= N / 2 + N % 2){
            dr = mid;
        }
        else{
            st = mid;
        }
    }

    cout << dr;
    return 0;
}
