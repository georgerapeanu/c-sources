#include <bits/stdc++.h>

using namespace std;

int v[int(2e5) + 5];

int main() {

    int n;
    
    cin >> n;

    if(n % 2 == 0)cout << "NO\n";
    else{
        cout << "YES\n";
        for(int i = 1;i <= n;i++){
            if(i % 2 == 1){
                v[i] = 2 * i - 1;
                v[i + n] = 2 * i;
            }
            else{
                v[i] = 2 * i;
                v[i + n] = 2 * i - 1;
            }
        }
        for(int i = 1;i <= 2 * n;i++){
            cout << v[i] << " ";
        }
    }

    return 0;
}
