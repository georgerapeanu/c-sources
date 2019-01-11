#include <cstdio>

using namespace std;

int change[35];

int main() {

    int n;
    scanf("%d",&n);

    int ans = 0;
    int xo = 0;

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        xo ^= val;
        for(int j = 0; j <= 30; j++) {
            val ^= ((val >> j) & 1) * change[j];
        }

        if(val) {
            ans++;
            int repr = 30;
            while(!((val >> repr) & 1)) {
                repr--;
            }

            for(int j = 0; j <= 30; j++) {
                if((change[j] >> repr) & 1) {
                    change[j] ^= val;
                }
            }

            change[repr]= val;
        }
    }

    printf("%d\n",xo == 0 ? -1:ans);

    return 0;
}
