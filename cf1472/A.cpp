#include <bits/stdc++.h>

using namespace std;

int t;
int h,w,n;

int main(){

    cin >> t;

    while(t--){
        cin >> h >> w >> n;

        int odd_h = h,odd_w = w;

        while(odd_h % 2 == 0){
            odd_h >>= 1;
        }
        while(odd_w % 2 == 0){
            odd_w >>= 1;
        }

        printf((h / odd_h) * (w / odd_w) >= n ? "YES\n":"NO\n");
    }

    return 0;
}
