#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2500;

int n;
pair<int,int> v[2 * NMAX + 5];

long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c) {
    return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

bool cmp(pair<int,int> &a,pair<int,int> &b) {
    bool h1 = a < v[1];
    bool h2 = b < v[1];

    if(h1 != h2) {
        return h1 < h2;
    }
    return det(v[1],a,b) > 0;
}

long long comb(int n,int k) {
    long long ans = 1;

    for(int i = n - k + 1; i <= n; i++) {
        ans *= i;
    }

    for(int i = 1; i <= k; i++) {
        ans /= i;
    }

    return ans;
}

int op[NMAX + 5];
long long solve() {
    sort(v + 2,v + 1 + n,cmp);

    for(int i = n + 1; i < 2 * n; i++) {
        v[i] = v[i - (n - 1)];
    }

    op[2] = 3;

    while(op[2] < 2 + (n - 1) && det(v[1],v[2],v[op[2]]) > 0) {
        op[2]++;
    }

    for(int i = 3; i <= n; i++) {
        op[i] = max(i + 1,op[i - 1]);
        while(op[i] < i + (n - 1) && det(v[1],v[i],v[op[i]]) > 0) {
            op[i]++;
        }
    }
    /*
        printf("\n\n\n");
        for(int i = 1;i <= n;i++){
            printf("%d %d %d %d %d %d\n",i,op[i],v[i].first,v[i].second,v[op[i]].first,v[op[i]].second);
        }
        printf("\n\n\n");
    */
    ///prepare for insertion of the first

    long long ans = 0;

    for(int i = 2; i <= n; i++) {
        ans += comb((op[i] - i) - 1,3);
    }

    return ans;
}

pair<int,int> b_v[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&v[i].first,&v[i].second);
        b_v[i] = v[i];
    }

    long long ans = 5 * comb(n,5);;

    for(int i = 1; i <= n; i++) {
        for(int i = 1; i <= n; i++) {
            v[i] = b_v[i];
        }
        swap(v[1],v[i]);
        ans -= solve();
//        printf("%d %d\n",i,ans);
    }

    printf("%lld\n",ans);

    return 0;
}
