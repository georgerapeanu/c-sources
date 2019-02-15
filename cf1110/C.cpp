#include <cstdio>

using namespace std;

int main() {
    int q;
    scanf("%d",&q);
    while(q--) {
        int a;
        scanf("%d",&a);
        int lg2 = 0;
        while(a >> lg2) {
            lg2++;
        }

        if(a == ((1 << lg2) - 1)) {
            int maxd = 1;
            for(int d = 2; 1LL * d * d <= a; d++) {
                if(a % d == 0) {
                    maxd = a / d;
                    break;
                }
            }
            printf("%d\n",maxd);
        }
        else {
            printf("%d\n",((1 << lg2) - 1));
        }
    }
    return 0;
}
