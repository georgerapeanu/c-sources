#include <iostream>

using namespace std;

int main() {

    string s;

    cin >> s;

    int st = 0,dr = (int)s.size() - 1;

    while(s[st] != '[' && st <= dr) {
        st++;
    }

    while(s[dr] != ']' && st <= dr) {
        dr--;
    }

    while(s[st] != ':' && st <= dr) {
        st++;
    }

    while(s[dr] != ':' && st <= dr) {
        dr--;
    }

    if(dr <= st) {
        cout << -1;
        return 0;
    }

    int ans = 4;

    for(int i = st; i <= dr; i++) {
        ans += (s[i] == '|');
    }

    cout << ans;

    return 0;
}
