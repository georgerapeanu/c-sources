#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

long long gauss[100000];
long long wut[64];

int main() {

    int t;
    scanf("%d",&t);

    while(t--) {
        int n;
        scanf("%d",&n);
        long long total_xor = 0;
        for(int i = 0; i < n; i++) {
            scanf("%lld",&gauss[i]);
            total_xor ^= gauss[i];
        }

        if(total_xor == 0) {
            printf("%d\n",0);
            continue;
        }

        int msb = 63;
        while(!(total_xor >> msb)) {
            msb--;
        }

        for(int i = 0; i < n; i++) {
            gauss[i] &= total_xor;
        }

        int lin = 0,col = 63;

        while(lin < n && col >= 0) {
            bool found = false;

            for(int i = lin; i < n; i++) {
                if((gauss[i] >> col) & 1) {
                    swap(gauss[lin],gauss[i]);
                    found = true;
                    break;
                }
            }

            if(!found) {
                wut[col] = -1;
                col--;
                continue;
            }

            for(int i = 0; i < n; i++) {
                if(i == lin) {
                    continue;
                }
                if(gauss[i] & (1LL << col)) {
                    gauss[i] ^= gauss[lin];
                }
            }

            wut[col] = lin;
            lin++;
            col--;
        }

        printf("%lld\n",gauss[wut[msb]] - (total_xor ^ gauss[wut[msb]]));
    }

    return 0;
}
