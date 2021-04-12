#include <iostream>
#include "aplusb.h"

int main() {
    int a, b;
    std::cin >> a >> b;

    int ans = aplusb(a, b);

    std::cout << ans << '\n';
    return 0;
}
