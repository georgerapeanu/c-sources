#include <iostream>

using namespace std;

int x,y,z;
int a,b,c;

int main() {
    cin >> x >> y >> z;
    cin >> a >> b >> c;
    if(x > a) {
        cout << "NO\n";
        return 0;
    }

    a -= x;
    b += a;

    if(y > b) {
        cout << "NO\n";
        return 0;
    }

    b -= y;
    c += b;

    if(z > c) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES";

    return 0;
}
