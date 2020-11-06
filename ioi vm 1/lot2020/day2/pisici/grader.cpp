#include <iostream>
#include "pisici.h"

int main() {
    int N;
    std::cin >> N;

    std::vector<int> t(N - 1), p(N - 1);
    for(int i = 0; i < N - 1; i++)
        std::cin >> t[i] >> p[i];

    long long ans = solve(N, t, p);

    std::cout << ans << '\n';
    return 0;
}
