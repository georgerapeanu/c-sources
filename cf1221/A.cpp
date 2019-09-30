#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int fr[30];

int main() {

    scanf("%d",&t);

    while(t--) {

        memset(fr,0,sizeof(fr));

        scanf("%d",&n);
        while(n--) {
            int a;
            scanf("%d",&a);
            int p = 0;
            while(a > 1) {
                a /= 2;
                p++;
            }
            fr[p]++;
        }

        for(int i = 0; i < 11; i++) {
            fr[i + 1] += (fr[i] / 2);
        }

        printf("%s\n",(fr[11] > 0 ? "YES":"NO"));
    }

    return 0;
}
