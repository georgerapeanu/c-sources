#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n,m;
int max_node[NMAX + 5];
int dsu[NMAX + 5];
pair<int,int> segm[NMAX + 5];

int fi(int x) {
    if(dsu[x] == 0) {
        return x;
    }
    return dsu[x] = fi(dsu[x]);
}

bool unite(int x,int y) {
    x = fi(x);
    y = fi(y);

    if(x == y) {
        return false;
    }

    dsu[x] = y;
    segm[y].first = min(segm[y].first,segm[x].first);
    segm[y].second = max(segm[y].second,segm[x].second);
    return true;
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        dsu[i] = 0;
        segm[i] = {i,i};
    }

    while(m--) {
        int x,y;
        scanf("%d %d",&x,&y);
        unite(x,y);
    }

    vector<pair<int,int> > tmp;

    for(int i = 1; i <= n; i++) {
        if(dsu[i] == 0) {
            tmp.push_back(segm[i]);
        }
    }

    sort(tmp.begin(),tmp.end());

    int ans = 0;

    for(int i = 1; i < (int)tmp.size(); i++) {
        if(tmp[i - 1].second >= tmp[i].first) {
            ans++;
            tmp[i].second = max(tmp[i].second,tmp[i - 1].second);
        }
    }

    printf("%d\n",ans);

    return 0;
}
