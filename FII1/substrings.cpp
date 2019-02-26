#include <iostream>

using namespace std;

int fr[400];

int main() {
    string a;

    int penis;

    cin >> penis;
    cin >> a;

    int st = 0;

    long long ans = 0;

    for(int dr = 0; dr < (int)a.size(); dr++) {
        fr[a[dr]]++;
        while(fr[a[dr]] > 1) {
            fr[a[st]]--;
            st++;
        }
        ans += (dr - st + 1);
    }

    cout << ans;
    return 0;
}
