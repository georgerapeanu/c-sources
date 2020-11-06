#include <cstdio>
#include "aplusb.h"

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    int ans = aplusb(a, b);

    printf("%d\n", ans);
    return 0;
}