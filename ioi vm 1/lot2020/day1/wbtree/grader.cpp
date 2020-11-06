#include <iostream>
#include "wbtree.h"

int main() {

    int N, K;
    std::cin >> N >> K;
    std::vector<int> p, q;
    for(int i = 1; i < N; i++) {
        int x, y;
        std::cin >> x >> y;
        p.push_back(x);
        q.push_back(y);
    }
    std::vector<int> r;
    for(int i = 1; i <= K; i++) {
        int x;
        std::cin >> x;
        r.push_back(x);
    }

    int ans = solve(N, p, q, r);

    std::cout << ans << std::endl;
    return 0;
}