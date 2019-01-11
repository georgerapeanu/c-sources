#include <cstdio>

using namespace std;

int main() {

    int t;

    scanf("%d",&t);

    while(t--) {
        int l,r,d;
        scanf("%d %d %d",&l,&r,&d);
        if(l / d > 1) {
            printf("%d\n",d);
        }
        else if(l / d == 1 && l % d != 0) {
            printf("%d\n",d);
        }
        else {
            printf("%d\n",(r / d) * d + d);
        }
    }

    return 0;
}
