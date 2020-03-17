#include <bits/stdc++.h>

using namespace std;

int main() {

    int x;

    scanf("%d",&x);

    if(x == 1) {
        printf("%d\n",1);
        return 0;
    }
    if(x == 2) {
        printf("%d\n",3);
        return 0;
    }


    for(int n = 1; n <= 100; n++) {
        if(n & 1) {
            int lat = (n - 1) / 2;
            int cnt = (lat * lat / 2) + (lat % 2 == 1);
            int tmp = lat / 2;
            if(4 * cnt + 4 * tmp + 1 >= x && x % 4 <= 1 + 2 * tmp) {
                printf("%d\n",n);
                return 0 ;
            }
        }
        else {
            if(x % 4 != 0) {
                continue;
            }
            int lat = (n / 2) - 1;
            int cnt = lat * lat / 2 + (lat % 2 == 1);
            if(cnt >= x / 4) {
                printf("%d\n",n);
                return 0;
            }
        }
    }

    return 0;
}
