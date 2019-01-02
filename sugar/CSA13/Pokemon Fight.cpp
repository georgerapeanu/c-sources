#include <iostream>
#include <set>

using namespace std;

int n,m;
multiset<int> poke;

int main() {

    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        poke.insert(val);
    }

    for(int i = 1; i <= m; i++) {
        int val;
        cin >> val;
        val++;
        if(poke.lower_bound(val) == poke.end()) {
            cout << -1;
            return 0;
        }
        poke.erase(poke.lower_bound(val));
    }

    long long sum = 0;
    for(auto it:poke) {
        sum += it;
    }

    cout << sum;

    return 0;
}