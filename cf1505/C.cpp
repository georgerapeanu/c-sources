#include <bits/stdc++.h>

using namespace std;

int main(){
    string s;

    cin >> s;

    bool ok = true;

    for(int i = 2;i < (int)s.size();i++){
        ok &= (s[i] - 'A' == ((s[i - 2] - 'A' + s[i - 1] - 'A') % ('Z' - 'A' + 1)));
    }

    cout << (ok ? "YES" : "NO");

    return 0;
}
