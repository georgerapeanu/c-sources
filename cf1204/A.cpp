#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;

    if(s.size() == 1 && s[0] == '0') {
        cout << "0";
        return 0;
    }

    bool hasTrain = ((int)s.size() % 2 == 1);

    for(int i = 1; i < (int)s.size(); i++) {
        hasTrain &= (s[i] == '0');
    }

    cout << ((int)s.size() + 1) / 2 - int(hasTrain);

    return 0;
}
