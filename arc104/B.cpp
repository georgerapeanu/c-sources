#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;
    string s;

    cin >> n >> s;

    pair<int,int> p = {0,0};

    map<pair<int,int>,int> mp;

    mp[p] = 1;

    int ans = 0;

    for(int i = 0;i < (int)s.size();i++){
        p.first += (s[i] == 'C');
        p.first -= (s[i] == 'G');
        p.second += (s[i] == 'A');
        p.second -= (s[i] == 'T');
        ans += mp[p];
        mp[p]++;
    }

    cout << ans << "\n";

    return 0;
}
