#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<int> solve(int n, vector<int> a, vector<int> b);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    vector<int> a(n - 1), b(n - 1);
    for (int i = 0; i < n - 1; ++i)
        cin >> a[i] >> b[i];

    auto r = solve(n, a, b);

    for (auto y : r)
        cout << y << '\n';

    return 0;
}
