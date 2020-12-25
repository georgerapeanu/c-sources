#include <bits/stdc++.h>

using namespace std;



int main(){

    int t;
    int x,y;

    cin >> t;

    while(t--){
        cin >> x >> y;
        cout << abs(x) + abs(y) + max(abs(abs(x) - abs(y)) - 1,0) << "\n";
    }

    return 0;
}
