#include <bits/stdc++.h>

using namespace std;

string s;
string ans;
set<int> rooms;

int main() {
    int n;
    cin >> n;
    cin >> s;

    ans = string(10,'0');

    for(int k = 0; k < 10; k++) {
        rooms.insert(k);
    }

    for(auto it:s) {
        if(it == 'L') {
            ans[*rooms.begin()] = '1';
            rooms.erase(rooms.begin());
        }
        else if(it == 'R') {
            ans[*rooms.rbegin()] = '1';
            rooms.erase(*rooms.rbegin());
        }
        else {
            rooms.insert(it - '0');
            ans[it - '0'] = '0';
        }
    }

    cout << ans;


    return 0;
}
