#include <bits/stdc++.h>

using namespace std;

int n,l,r;

int main() {

    cin >> n >> l >> r;

    cout << (n - l) + (1 << l) - 1 << " " << ((n - r + 2) << (r - 1)) - 1 << endl;

    return 0;
}
