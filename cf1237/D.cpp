#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int v[3 * NMAX + 5];
int ans[3 * NMAX + 5];

int nxt[3 * NMAX + 5];
int st[3 * NMAX + 5],len;

struct event_t {
    int val;
    int wh;
    int typ;

    bool operator < (const event_t &other)const {
        if(val != other.val) {
            return val < other.val;
        }
        if(typ != other.typ) {
            return typ < other.typ;
        }
        return wh < other.wh;
    }
};

vector<event_t> events;
set<int> s;

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        events.push_back({v[i],i,0});
        events.push_back({(v[i] - 1) / 2,i,1});
    }

    for(int i = n + 1; i <= 3 * n; i++) {
        v[i] = v[i - n];
        events.push_back({v[i],i,0});
        events.push_back({(v[i] - 1) / 2,i,1});
    }

    for(int i = 3 * n; i; i--) {
        while(len > 0 && v[st[len]] < v[i]) {
            len--;
        }

        if(len == 0) {
            nxt[i] = 3 * n + 1;
        }
        else {
            nxt[i] = st[len];
        }

        st[++len] = i;
    }

    sort(events.begin(),events.end());

    for(auto it:events) {
        if(it.typ == 0) {
            s.insert(it.wh);
        }
        else {
            if(s.lower_bound(it.wh) != s.end() && *s.lower_bound(it.wh) <= nxt[it.wh]) {
                ans[it.wh] = *s.lower_bound(it.wh) - it.wh;
            }
        }
    }

    for(int i = 3 * n; i; i--) {
        if(ans[i] == 0) {
            ans[i] = ans[nxt[i]] + (nxt[i] - i);
        }
    }

    for(int i = 1; i <= n; i++) {
        printf("%d ",(ans[i] == 3 * n - i + 1 ? -1:ans[i]));
    }

    return 0;
}
