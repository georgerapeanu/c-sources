#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;
pair<int,int> v[NMAX + 5];

bool ok(int st,int dr) {
    int r = v[st + 1].first - v[st].first;
    for(int i = st; i < dr; i++) {
        if(v[i + 1].first - v[i].first != r) {
            return false;
        }
    }
    return true;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i].first);
        v[i].second = i;
    }

    if(n <= 3) {
        printf("1\n");
        return 0;
    }

    sort(v + 1,v + 1 + n);

    if(ok(2,n)) {
        printf("%d\n",v[1].second);
        return 0;
    }

    swap(v[1],v[2]);

    if(ok(2,n)) {
        printf("%d\n",v[1].second);
        return 0;
    }

    swap(v[1],v[2]);

    int pos = -1,r = v[2].first - v[1].first;

    for(int i = 1; i < n; i++) {
        if(v[i + 1].first - v[i].first != r) {
            pos = i + 1;
            break;
        }
    }

    swap(v[1],v[pos]);

    sort(v + 2,v + 1 + n);

    if(ok(2,n)) {
        printf("%d\n",v[1].second);
        return 0;
    }
    else {
        printf("-1");
    }

    return 0;
}
