#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int x[55];
bool exists[55];

int main(){

    cin >> t;
    while(t--){
        cin >> n;

        for(int i = 1;i <= 50;i++){
            exists[i] = false;
        }
    
        for(int i = 1;i <= n;i++){
            cin >> x[i];
        }
    
        for(int i = 1;i <= n;i++){
            for(int j = i + 1;j <= n;j++){
                exists[x[j] - x[i]] = true;
            }
        }
    
        int ans = 0;
    
        for(int i = 1;i <= 50;i++){
            ans += (exists[i] == true);
        }

        cout << ans << "\n";
    }
    return 0;
}
