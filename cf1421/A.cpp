#include <bits/stdc++.h>

using namespace std;

int t;
int a,b;

int main(){

    cin >> t;

    while(t--){
        cin >> a >> b;

        int ans = 0;

        for(int k = 0;k <= 30;k++){
            if(((a >> k) & 1) != ((b >> k) & 1)){
                ans |= (1 << k);
            }
        }
        
        cout << ans << "\n";
    }

    return 0;
}
