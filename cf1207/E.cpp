#include <bits/stdc++.h>

using namespace std;

int main() {


    cout << "? ";

    for(int x = 0,cnt = 1;cnt <= 100;cnt++,x += (1 << 7)){
        cout << x << " ";
    }

    cout << endl;

    int ans = 0,tmp;

    cin >> tmp;

    ans |= (tmp & ((1 << 7) - 1));

    cout << "? ";

    for(int x = 1,cnt = 1;cnt <= 100;cnt++,x++){
        cout << x << " ";
    }

    cout << endl;

    cin >> tmp;

    ans |= (tmp & (((1 << 7) - 1) << 7));

    cout << "! " << ans << endl;

    return 0;
}
