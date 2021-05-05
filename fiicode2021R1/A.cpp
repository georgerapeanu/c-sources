#include <bits/stdc++.h>

using namespace std;

int main(){

    int n;

    cin >> n;

    int ans = 0;
    while(n--){
        int value;
        cin >> value;
        ans += __builtin_popcount(value) - 1;
    }

    cout << ans;

    return 0;
}
