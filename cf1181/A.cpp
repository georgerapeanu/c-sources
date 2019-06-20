#include <bits/stdc++.h>

using namespace std;

long long x,y,z;

int main() {

    cin >> x >> y >> z;

    if((x / z) + (y / z) != ((x + y) / z)) {
        cout << (x + y) / z << " " << z - max(x % z,y % z) << "\n";
    }
    else {
        cout << x / z + y / z << " " << 0 << "\n";
    }

    return 0;
}
