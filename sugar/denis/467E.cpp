#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int NMAX = 5e5;

int n;
int aint[4 * NMAX + 5];
int lazy[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || lazy[nod] == 0) {
        return ;
    }
    aint[2 * nod] = max(aint[2 * nod],lazy[nod]);
    lazy[2 * nod] = max(lazy[2 * nod],lazy[nod]);
    aint[2 * nod + 1] = max(aint[2 * nod + 1],lazy[nod]);
    lazy[2 * nod + 1] = max(lazy[2 * nod + 1],lazy[nod]);

    lazy[nod] = 0;
}

void update(int nod,int st,int dr,int S,int D,int val) {
    propag(nod,st,dr);

    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        lazy[nod] = val;
        aint[nod] = max(aint[nod],val);
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);

    aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
}

int query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);
    if(D < st || S > dr) {
        return 0;
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
}

int v[NMAX + 5];
int dp[NMAX + 5];
int ant[NMAX + 5];
int val_nxt[NMAX + 5];
int val_ant[NMAX + 5];
unordered_map<int,vector<int> > lst;
bool same[NMAX + 5];


int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        ant[i] = i - 1;
        if(lst.count(v[i])) {
            int tmp = query(1,1,n,lst[v[i]].back(),lst[v[i]].back());
            if(tmp > 0) {
                if(dp[i] < dp[tmp - 1] + 1) {
                    dp[i] = dp[tmp - 1] + 1;
                    ant[i] = tmp - 1;
                }
            }

            if(lst[v[i]].back() != i - 1) {
                update(1,1,n,lst[v[i]].back() + 1,i - 1,lst[v[i]].back());
            }
            val_nxt[lst[v[i]].back()] = i;
            val_ant[i] = lst[v[i]].back();

            if(lst[v[i]].size() >= 3) {
                if(dp[i] < dp[lst[v[i]][(int)lst[v[i]].size() - 3] - 1] + 1) {
                    same[i] = true;
                    dp[i] = dp[lst[v[i]][(int)lst[v[i]].size() - 3] - 1] + 1;
                    ant[i] = lst[v[i]][(int)lst[v[i]].size() - 3] - 1;
                }
            }
        }
        lst[v[i]].push_back(i);
    }

    printf("%d\n",4 * dp[n]);

    int pos = n;

    vector<int> tmp;

    while(pos) {
        if(ant[pos] != pos - 1) {
            if(same[pos]) {
                for(int k = 0; k < 4; k++) {
                    tmp.push_back(v[pos]);
                }
            }
            else {
                tmp.push_back(v[pos]);
                tmp.push_back(v[val_nxt[ant[pos] + 1]]);
                tmp.push_back(v[val_ant[pos]]);
                tmp.push_back(v[ant[pos] + 1]);
            }
        }
        pos = ant[pos];
    }

    reverse(tmp.begin(),tmp.end());

    for(auto it:tmp) {
        printf("%d ",it);
    }

    return 0;
}
