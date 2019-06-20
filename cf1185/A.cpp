#include <bits/stdc++.h>

using namespace std;

int main() {
    int a,b,c,d;
    cin >> a >> b >> c >> d;

    vector<int> v = {a,b,c};

    sort(v.begin(),v.end());

    cout << 1LL * max(0,d - (v[1] - v[0])) + 1LL * max(0,d - (v[2] - v[1]));

    return 0;
}
