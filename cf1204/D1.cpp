#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

string s;
string t;

int main() {
    cin >> s;
    s = " " + s;
    t = string(s.size(),' ');

    int cnt0 = -1;

    for(int i = (int)s.size() - 1; i; i--) {
        if(s[i] == '1') {
            if(cnt0 >= 0) {
                cnt0--;
                t[i] = '1';
            }
            else {
                t[i] = '0';
            }
        }
        else {
            if(i < (int)s.size() - 1 && s[i + 1] == '1') {
            }
            cnt0++;
            t[i] = '0';
        }
    }

    cout << t.substr(1);

    return 0;
}
