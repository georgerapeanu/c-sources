#include <bits/stdc++.h>

using namespace std;

const long long LIM = (1LL << 32);

long long t;

int main() {

    cin >> t;

    vector<long long> cnt;
    vector<long long> p = {1};
    long long ans = 0;
    while(t--) {
        string cmd;
        cin >> cmd;

        if(cmd == "for") {
            long long n;
            cin >> n;
            cnt.push_back(n);
            p.push_back(min(LIM,p.back() * n));
        }
        else if(cmd == "add") {
            if(ans + p.back() >= LIM) {
                cout << "OVERFLOW!!!";
                return 0;
            }
            ans += p.back();
        }
        else {
            cmd.pop_back();
            p.pop_back();
        }
    }

    cout << ans;

    return 0;
}
