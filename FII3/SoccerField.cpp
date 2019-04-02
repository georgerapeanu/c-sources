#include <iostream>

using namespace std;

int main() {
    int l1,h1,l2,h2;
    cin >> l1 >> h1 >> l2 >> h2;
    int ans = max(l1 * h1,l2 * h2);
    ans = max(ans,(l1 + l2) * min(h1,h2));
    ans = max(ans,(l1 + h2) * min(h1,l2));
    ans = max(ans,(h1 + l2) * min(l1,h2));
    ans = max(ans,(h1 + h2) * min(l1,l2));

    cout << ans;
    return 0;
}
