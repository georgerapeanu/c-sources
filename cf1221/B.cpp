#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;
    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            printf("%c",((i % 2 != j % 2) ? 'B':'W'));
        }
        printf("\n");
    }

    return 0;
}
