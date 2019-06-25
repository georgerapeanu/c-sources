#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 3e5;

int n,q;

deque<int> dq;
pair<int,int> op[NMAX + 5];

int ma = 0;

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d",&x);
        dq.push_back(x);
        ma = max(ma,x);
    }

    int last = 0;

    while(dq.front() != ma) {
        int a = dq.front();
        dq.pop_front();
        int b = dq.front();
        dq.pop_front();

        op[++last] = {a,b};

        if(a < b) {
            swap(a,b);
        }

        dq.push_front(a);
        dq.push_back(b);
    }

    while(q--) {
        long long x;
        scanf("%lld",&x);

        if(x <= last) {
            printf("%d %d\n",op[x].first,op[x].second);
        }
        else {
            x -= last;
            printf("%d %d\n",dq.front(),dq[((x - 1) % (n - 1)) + 1]);
        }
    }

    return 0;
}
