#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;
    s = " " + s;
    string repr(2 * n + 1,' ');
    for(int i = 1;i <= 2 * n;i++){
        repr[i] = '0' + ((s[i] == 'B') == (2 * n - i + 1) % 2);
    }
    
    int ans = 1;
    int cnt0 = 0;

    for(int i = 1;i <= 2 * n;i++){
        if(repr[i] == '0'){
            cnt0++;
        }
        else{
            if(cnt0 <= 0){
                ans = 0;
                break;
            }
            ans = 1LL * ans * cnt0 % MOD;
            cnt0--;
        }
    }

    if(cnt0 > 0){
        ans = 0;
    }

    for(int i = 1;i <= n;i++){
        ans = 1LL * ans * i % MOD;
    }

    cout << ans << "\n";

    return 0;
}
