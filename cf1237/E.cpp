#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d",&n);

    int x = 1;

    while(x <= n) {
        if(x == n || x + 1 == n) {
            printf("1\n");
            return 0;
        }
        if(x % 2 == 1) {
            x = (x + 1) + x + 1;
        }
        else {
            x = x + x + 1;
        }
    }

    printf("0\n");

    return 0;
}
