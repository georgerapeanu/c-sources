#include <bits/stdc++.h>

using namespace std;

int main() {

    int n,b,g;
    cin >> b >> g >> n;

    int ans = 0;

    for(int i = 0;i <= n;i++){
        if(i <= b && n - i <= g){
            ans++;
        }
    }

    cout << ans;

    return 0;
}
