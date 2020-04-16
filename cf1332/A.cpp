#include <bits/stdc++.h>

using namespace std;

int t;
int x,y,stx,sty,drx,dry;
int a,b,c,d;

int main() {

    cin >> t;

    while(t--) {
        cin >> a >> b >> c >> d;
        cin >> x >> y >> stx >> sty >> drx >> dry;
        if(((stx <= x + (b - a) && x + (b - a) <= drx) && (stx != drx || (a == 0 && b == 0))) && ((sty <= y + (d - c) && y + (d - c) <= dry && (sty != dry || (c == 0 && d == 0))))) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }

    return 0;
}
