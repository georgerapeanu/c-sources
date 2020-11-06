#include <iostream>
#include "permutare.h"

int main() {

    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> p;
    for(int i = 0; i < N; i++) {
        int x;
        std::cin >> x;
        p.push_back(x);
    }

    int ans = init(p);
    std::cout << ans << std::endl;

    for(int i = 0; i < Q; i++) {
        int x, y;
        std::cin >> x >> y;
        int ans = query(x, y);
        std::cout << ans << std::endl;
    }

    return 0;
}