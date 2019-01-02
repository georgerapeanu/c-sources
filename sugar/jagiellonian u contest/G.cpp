#include <cstdio>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int t;
char c[30];
int viz[1 << 20];
int father[1 << 20];
int cnt[1 << 20];
vector<pair<int,int> > edges[21];

int fi(int nod) {
    if(father[nod] < 0) {
        return nod;
    }
    return father[nod] = fi(father[nod]);
}

bool u(int x,int y) {
    x = fi(x);
    y = fi(y);
    if(x == y) {
        return false;
    }

    if(father[x] < father[y]) {
        father[x] += father[y];
        father[y] = x;
    }
    else {
        father[y] += father[x];
        father[x] = y;
    }
    return true;
}

int main() {
    for(int i = 0; i < (1 << 20); i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    // freopen("in","r",stdin);
    // freopen("out","w",stdout);

    scanf("%d\n",&t);

    while(t--) {
        for(int i = 0; i < (1 << 20); i++) {
            viz[i] = -1;
            father[i] = -1;
        }

        for(int i = 0; i <= 20; i++) {
            edges[i].clear();
        }

        int n,m;
        scanf("%d %d\n",&m,&n);
        queue<int> q;

        for(int i = 0; i < n; i++) {
            fgets(c,30,stdin);
            int val = 0;
            for(int j = 0; j < m; j++) {
                val |= ((c[j] == 'R') << j);
            }
            viz[val] = val;
            q.push(val);
        }

        while(!q.empty()) {
            int nod = q.front();
            q.pop();
            for(int b = 0; b < m; b++) {
                if(viz[nod ^ (1 << b)] == -1) {
                    viz[nod ^ (1 << b)] = viz[nod];
                    q.push(nod ^ (1 << b));
                }
                else if(viz[nod ^ (1 << b)] != viz[nod]) {
                    edges[cnt[viz[nod] ^ viz[nod ^ (1 << b)]]].push_back({viz[nod],viz[nod ^ (1 << b)]});
                }
            }
        }

        int cost = 0;

        for(int x = 0; x <= 20; x++) {
            for(auto it:edges[x]) {
                cost += u(it.first,it.second) * x;
            }
        }

        printf("%d\n",cost);
    }

    return 0;
}