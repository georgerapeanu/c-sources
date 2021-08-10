#include "saumat.h"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    assert(cin >> N >> M);

    vector<int> P(1024);
    for (auto &x : P)
        assert(cin >> x);

    vector<vector<int>> A(N, vector<int>(M, 0));
    for (auto &x : A)
        for (auto &y : x)
            cin >> y;

    cout << solve(P, N, M, A) << endl;

    return 0;
}
