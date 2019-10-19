#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n;
int x,a;
int y,b;
int p[NMAX + 5];
int wut[NMAX + 5];
long long k;

int tmp[NMAX + 5];

bool ok(int pos){
    for(int i = 1;i <= pos;i++){
        tmp[i] = wut[i];
    }

    sort(tmp + 1,tmp + 1 + pos);
    reverse(tmp + 1,tmp + 1 + pos);

    long long ans = 0;

    for(int i = 1;i <= pos;i++){
        ans += 1LL * tmp[i] * p[i];
    }

    return ans >= k;
}

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            wut[i] = 0;
            scanf("%d",&p[i]);
            p[i] /= 100;
        }

        scanf("%d %d\n",&x,&a);
        scanf("%d %d\n",&y,&b);
        scanf("%lld",&k);

        sort(p + 1,p + 1 + n);
        reverse(p + 1,p + 1 + n);

        for(int i = a;i <= n;i += a){
            wut[i] += x;
        }

        for(int i = b;i <= n;i += b){
            wut[i] += y;
        }

        int l = 0,r = n + 1;

        while(r - l > 1){
            int mid = (l + r) / 2;

            if(ok(mid)){
                r = mid;
            }
            else{
                l = mid;
            }
        }

        printf("%d\n",(r == n + 1 ? -1:r));
    }

    return 0;
}
