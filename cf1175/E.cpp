#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int XMAX = 5e5;
const int LGMAX = 19;

int n,m;
vector< pair<int,int> > events;

int nxt[LGMAX + 1][XMAX + 1];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        int l,r;
        scanf("%d %d",&l,&r);
        events.push_back({l,r});
    }

    sort(events.begin(),events.end());
    reverse(events.begin(),events.end());

    int lst = -1;

    for(int i = 0; i <= XMAX; i++) {
        while(events.size() && events.back().first <= i) {
            lst = max(events.back().second,lst);
            events.pop_back();
        }
        nxt[0][i] = max(i,lst);
    }

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 0; i <= XMAX; i++) {
            nxt[h][i] = nxt[h - 1][nxt[h - 1][i]];
        }
    }

    while(m--) {
        int l,r;
        scanf("%d %d",&l,&r);
        if(nxt[LGMAX][l] < r) {
            printf("-1\n");
        }
        else {
            int ans = 0;
            int pos = l;
            for(int h = LGMAX; h >= 0; h--) {
                if(nxt[h][pos] < r) {
                    pos = nxt[h][pos];
                    ans += (1 << h);
                }
            }
            printf("%d\n",++ans);
        }
    }

    return 0;
}
