#include <bits/stdc++.h>

using namespace std;

int QMAX = 1e6;
int KMAX = 20;
long long XMAX = 1e18;
long long DMAX = 1e18;

int main() {

    mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());

    int subtask_id = -1;

    scanf("%d",&subtask_id);

    if(subtask_id == 1) {
        KMAX = 1;
    } else if(subtask_id == 2) {
        QMAX = 1e5;
        DMAX = 10;
    } else if(subtask_id == 3) {
        XMAX = 1e6;
    } else if(subtask_id == 4) {
        ;
    } else {
        fprintf(stderr,"something went wrong");
        assert(false);
    }

    int q = QMAX;

    printf("%d\n",q);

    for(int i = 1; i <= q; i++) {
        int k = min((i + 1)/ 2,KMAX);
        long long l = gen() % XMAX + 1;
        long long r = l + (gen() % min(DMAX - 1,XMAX - l + 1));

        assert(0 <= l);
        assert(l <= r);
        assert(r <= XMAX);
        assert(r - l + 1 <= DMAX);

        printf("%d %lld %lld\n",k,l,r);
    }

    return 0;
}
