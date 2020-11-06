#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;
vector<int> graph[NMAX + 5];

int w[NMAX + 5];

void predfs(int nod,int tata) {
    w[nod] = 1;
    for(auto it:graph[nod]) {
        if(it != tata) {
            predfs(it,nod);
            w[nod] += w[it];
        }
    }
}

inline void add(map<int,int> &s,int val) {
    s[val]++;
}

inline void rem(map<int,int> &s,int val) {
    s[val]--;
    if(s[val] == 0) {
        s.erase(val);
    }
}

int compute(int a,int b,int c) {
    return max(max(a,b),c) - min(min(a,b),c);
}

int ans = 1e9;
map<int,int> a,b;

void dfs(int nod,int tata) {

    if(tata != 0) {
        map<int,int> :: iterator it;
        it = b.lower_bound((n - w[nod]) / 2);
        if(it != b.end()) {
            ans = min(ans,compute(w[nod],n - w[nod] - it->first,it->first));
        }
        if(it != b.begin()) {
            it--;
            ans = min(ans,compute(w[nod],n - w[nod] - it->first,it->first));
        }

        it = a.lower_bound((n + w[nod]) / 2);
        if(it != a.end()) {
            ans = min(ans,compute(w[nod],n - it->first,it->first - w[nod]));
        }
        if(it != a.begin()) {
            it--;
            ans = min(ans,compute(w[nod],n - it->first,it->first - w[nod]));
        }
    }

    add(a,w[nod]);

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
    }

    rem(a,w[nod]);
    add(b,w[nod]);
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    predfs(1,0);
    dfs(1,0);

    printf("%d\n",ans);

    return 0;
}
