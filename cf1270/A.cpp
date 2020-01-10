#include <bits/stdc++.h>

using namespace std;

int t,n,x,y;

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d %d",&n,&x,&y);
        int ma1 = 0;
        int ma2 = 0;

        for(int i = 1; i <= x; i++) {
            int val;
            scanf("%d",&val);
            ma1 = max(ma1,val);
        }

        for(int i = 1; i <= y; i++) {
            int val;
            scanf("%d",&val);
            ma2 = max(ma2,val);
        }

        if(ma1 > ma2) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}
