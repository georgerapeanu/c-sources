#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        if(n == 1){
            cout << "9\n";
            continue;
        }
        cout << "98";
        int cf = 9;
        for(int i = 3;i <= n;i++){
            cout << cf;
            cf = (cf == 9 ? 0:cf + 1);
        }
        cout << "\n";
    }


    return 0;
}
