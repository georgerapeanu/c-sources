#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,m;
int q;

vector<string> a;
vector<string> b;

int main() {

    cin >> n >> m;

    a.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    b.resize(m);
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }
    cin >> q;

    while(q--) {
        int val;
        cin >> val;
        cout << (a[(val - 1) % n] + b[(val - 1) % m]) << "\n";
    }

    return 0;
}
