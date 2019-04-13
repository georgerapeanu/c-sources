#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
int a[NMAX + 5];
int aib[NMAX + 5];

int dpl[NMAX + 5];
int dpr[NMAX + 5];

void update(int pos,int val) {
    for(; pos <= NMAX; pos += (-pos) & pos) {
        aib[pos] = max(aib[pos],val);
    }
}

int query(int pos) {
    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans = max(ans,aib[pos]);
    }
    return ans;
}

void reset() {
    for(int i = 1; i <= NMAX; i++) {
        aib[i] = 0;
    }
}

int fr[NMAX + 5];

int ans[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    for(int i = 1; i <= n; i++) {
        dpl[i] = 1 + query(a[i] - 1);
        update(a[i],dpl[i]);
    }

    reset();

    for(int i = n; i; i--) {
        dpr[i] = 1 + query(NMAX - a[i]);
        update(NMAX - a[i] + 1,dpr[i]);
    }

    int l = 0;

    for(int i = 1; i <= n; i++) {
        l = max(l,dpl[i]);
    }

    for(int i = 1; i <= n; i++) {
        if(dpl[i] + dpr[i] == l + 1) {
            fr[dpl[i]]++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(dpl[i] + dpr[i] < l + 1) {
            printf("1");
        }
        else if(fr[dpl[i]] != 1) {
            printf("2");
        }
        else {
            printf("3");
        }
    }

    return 0;
}
