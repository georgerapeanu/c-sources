#include <bits/stdc++.h>

using namespace std;

int t;
int n,m,k;

int main(){

    cin >> t;

    while(t--){
        cin >> n >> m >> k;  
        cout << (n * m - 1 == k ? "YES":"NO") << "\n";
    }


    return 0;
}
