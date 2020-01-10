#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n,s;
int a[NMAX + 5];


int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d",&n,&s);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
        }

        int pref = 1;
        int sum = 0;

        while(pref <= n && sum <= s - a[pref]) {
            sum += a[pref];
            pref++;
        }

        if(pref == n + 1) {
            printf("0\n");
        }
        else {
            int tmp_ans = pref - 1;
            int ma = 0;
            for(int i = 1; i <= pref; i++) {
                if(ma == 0 || a[ma] < a[i]) {
                    ma = i;
                }
            }
            sum -= a[ma];
            while(pref <= n && sum <= s - a[pref]) {
                sum += a[pref];
                pref++;
            }
            if(tmp_ans > pref - 2) {
                printf("0\n");
            }
            else {
                printf("%d\n",ma);
            }
        }
    }

    return 0;
}
