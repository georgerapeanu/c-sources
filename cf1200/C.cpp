#include <bits/stdc++.h>

using namespace std;

long long n,m;
long long fst_pos;
long long snd_pos;
int q;

long long gcd(long long a,long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}
long long get_zone(long long x,long long y) {
    if(x == 1) {
        return (y - 1) / fst_pos + 1;
    }
    else {
        return (y - 1) / snd_pos + 1;
    }
}
int main() {

    scanf("%lld %lld %d",&n,&m,&q);

    long long g = gcd(n,m);

    fst_pos = n / g;
    snd_pos = m / g;

    while(q--) {
        long long x,y,xx,yy;
        scanf("%lld %lld %lld %lld",&x,&y,&xx,&yy);
        if(get_zone(x,y) == get_zone(xx,yy)) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}
