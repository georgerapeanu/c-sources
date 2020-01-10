#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int NMAX = 1e5;

int n;
map<int,int> to_norm;
pair<pair<int,int>,pair<int,int> > v[NMAX + 5];

bool aint[16 * NMAX + 5];
bool lazy[16 * NMAX + 5];

void init(int nod,int st,int dr) {
    aint[nod] = lazy[nod] = false;
    if(st == dr) {
        return ;
    }
    int mid = (st + dr) / 2;
    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);
}

void propag(int nod,int st,int dr) {
    if(st == dr || lazy[nod] == false) {
        return;
    }
    lazy[nod * 2] = true;
    lazy[nod * 2 + 1] = true;
    aint[nod * 2] = true;
    aint[nod * 2 + 1] = true;
}

void update(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(r < st || l > dr) {
        return ;
    }

    if(l <= st && dr <= r) {
        aint[nod] = lazy[nod] = true;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r);
    update(nod * 2 + 1,mid + 1,dr,l,r);

    aint[nod] = aint[2 * nod] | aint[2 * nod + 1];
}

bool query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(r < st || l > dr) {
        return false;
    }

    if(l <= st && dr <= r) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) | query(nod * 2 + 1,mid + 1,dr,l,r);
}

bool solve() {
    vector<pair<int,int> > events;

    for(int i = 1; i <= n; i++) {
        events.push_back({v[i].first.first,-i});
        events.push_back({v[i].first.second,i});
    }

    sort(events.begin(),events.end());

    init(1,1,to_norm.size());

    for(auto it:events) {
        int i = it.second;
        if(it.second > 0) {
            update(1,1,to_norm.size(),to_norm[v[i].second.first],to_norm[v[i].second.second]);
        }
        else {
            if(query(1,1,to_norm.size(),to_norm[v[-i].second.first],to_norm[v[-i].second.second]) == true) {
                return false;
            }
        }
    }
    return true;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d %d",&v[i].first.first,&v[i].first.second,&v[i].second.first,&v[i].second.second);
        to_norm[v[i].first.first] = 1;
        to_norm[v[i].first.second] = 1;
        to_norm[v[i].second.first] = 1;
        to_norm[v[i].second.second] = 1;
    }

    int last = 0;

    for(auto &it:to_norm) {
        it.second = ++last;
    }

    if(solve() == false) {
        printf("NO\n");
        return 0;
    }

    for(int i = 1; i <= n; i++) {
        swap(v[i].first,v[i].second);
    }

    if(solve() == false) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    return 0;
}
