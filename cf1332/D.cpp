#include <bits/stdc++.h>

using namespace std;

int main() {
    const int LGMAX = 17;
    const int VMAX = 1 << LGMAX;
    int k;

    cin >> k;

    cout << "3 3\n";

    cout << VMAX + k << " " << VMAX << " " << 0 << "\n";
    cout << k << " " << VMAX + k << " " << k << "\n";
    cout << 0 << " " << k << " " << k << "\n";

    return 0;
}
