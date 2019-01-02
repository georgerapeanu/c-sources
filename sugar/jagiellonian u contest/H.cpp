#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 1e5;
int r[NMAX + 5];
int c[NMAX + 5];

int main() {

    int t;
    scanf("%d",&t);

    while(t--) {
        int n;
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&r[i]);
        }

        for(int i = 1; i <= n; i++) {
            scanf("%d",&c[i]);
        }

        int r1 = 1,c1 = 1,r2 = 1,c2 = 1;
        int ans = 1;


        while(r1 != n || r2 != n || c1 != n || c2 != n) {
            if(r1 > n || r2 > n || c1 > n || c2 > n) {
                ans = 0;
                break;
            }
            if(r1 == r2 && c1 == c2) {
                r[r1]--;
                c[c1]--;
                if(r[r1] == 0) {
                    r1++;
                    r2++;
                }
                else if(c[c1] == 0) {
                    c1++;
                    c2++;
                }
                else {
                    r1++;
                    c2++;
                    ans <<= 1;
                    if(ans >= MOD) {
                        ans -= MOD;
                    }
                }
            }
            else {
                if(r1 > r2 || (r1 == r2 && c1 > c2)) {
                    swap(r1,r2);
                    swap(c1,c2);
                }
                r[r1]--;
                c[c1]--;
                if(r1 == r2) {
                    if(c[c1] > 0) {
                        r1++;
                    }
                    else if(r[r1] > 0) {
                        c1++;
                    }
                    else {
                        ans = 0;
                        break;
                    }
                    continue;
                }
                if(r[r1] > 0) {
                    c1++;
                }
                else if(c[c1] > 0) {
                    r1++;
                }
                else {
                    ans = 0;
                    break;
                }

            }

        }
        r[n]--;
        c[n]--;
        for(int i = 1; i <= n; i++) {
            if(!(r[i] == 0 && c[i] == 0)) {
                ans = 0;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}