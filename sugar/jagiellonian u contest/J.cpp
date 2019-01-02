#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

const double eps = 1e-9;
long double num[150005];
long double sp[150005];

int main() {

    for(int i = 2; i <= 150000; i++) {
        num[i] = log(i);
        sp[i] = num[i] + sp[i - 1];
    }

    int z;

    scanf("%d",&z);

    while(z--) {
        long double xlog = 0;
        int t,m;
        scanf("%d %d",&t,&m);
        for(int i = 1; i <= t; i++) {
            int x;
            scanf("%d",&x);
            xlog += num[x];
        }

        int ind = m;
        bool found = false;
        for(int i = 1; i <= m; i++) {
            ind = max(ind,i);
            while(ind > i && eps < (sp[ind] - sp[ind - i]) - (xlog + sp[i])) {
                ind--;
            }

            if(abs((sp[ind] - sp[ind - i]) - (xlog + sp[i])) < eps) {
                printf("YES\n");
                printf("%d %d\n",ind,i);
                found = true;
                break;
            }
        }
        if(!found) {
            printf("NO\n");
        }
    }

    return 0;
}
