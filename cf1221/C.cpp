#include <bits/stdc++.h>

using namespace std;

int t;
int c,m,x;

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d %d",&c,&m,&x);
        if(c < m) {
            swap(c,m);
        }
        x += c - m;
        c = m;

        if(x < c) {
            int tmp = (c - x) / 3;
            int ans = min(m - tmp,x + 2 * tmp);
            tmp++;
            ans = max(ans,min(m - tmp,x + 2 * tmp));
            printf("%d\n",ans);
        }
        else {
            printf("%d\n",m);
        }

    }

    return 0;
}
