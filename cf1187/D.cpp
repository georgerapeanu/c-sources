#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int VMAX = 3e5;

int t;
int n;
int aint[4 * NMAX + 5];
deque<int> pos[VMAX + 5];

int source[NMAX + 5];
int target[NMAX + 5];

void build(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod] = source[st];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = min(aint[2 * nod],aint[2 * nod + 1]);
}

void update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod] = val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = min(aint[2 * nod],aint[2 * nod + 1]);
}

int query(int nod,int st,int dr,int S,int D) {
    if(dr < S || st > D) {
        return VMAX + 5;
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return min(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
}

void init() {
    for(int i = 1; i <= n; i++) {
        pos[i].clear();
    }

    for(int i = 1; i <= n; i++) {
        pos[source[i]].push_back(i);
    }

    build(1,1,n);
}

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i++) {
            scanf("%d",&source[i]);
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d",&target[i]);
        }

        init();

        bool ok = true;

        for(int i = 1; i <= n; i++) {
            if(pos[target[i]].empty() || query(1,1,n,1,pos[target[i]].front()) < target[i]) {
                ok = false;
                break;
            }
            update(1,1,n,pos[target[i]].front(),VMAX + 5);
            pos[target[i]].pop_front();
        }
        if(ok == true) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }


    return 0;
}
