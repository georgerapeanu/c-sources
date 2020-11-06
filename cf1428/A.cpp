#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin >> t;
    while(t--){
        int x,y,xx,yy;
        cin >> x >> y >> xx >> yy;
        cout << abs(x - xx) + abs(y - yy) + (x != xx && y != yy) * 2 << "\n";
    }

    return 0;
}
