#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("sortnet.in","r");
FILE *g = fopen("sortnet.out","w");

int n,m;
pair<int,int> op[15];
pair<int,int> to[1 << 20];
int state[1 << 20];
bool ok[1 << 20];

int calc(int conf) {
    for(int i = 1; i <= n / 2; i++) {
        if(((conf >> op[i].first) & 1) > ((conf >> op[i].second) & 1)) {
            conf -= (1 << op[i].first);
            conf += (1 << op[i].second);
        }
    }
    return conf;
}

int main() {

    fscanf(f,"%d %d\n",&n,&m);

    for(int i = 0; i < (1 << n); i++) {
        state[i] = i;
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n / 2; j++) {
            fscanf(f,"<%d,%d> ",&op[j].first,&op[j].second);
            op[j].first--;
            op[j].second--;
        }
        for(int conf = 0; conf < (1 << n); conf++) {
            if(to[state[conf]].first != i) {
                to[state[conf]] = {i,calc(state[conf])};
            }
            state[conf] = to[state[conf]].second;
        }
    }

    for(int pref = 0; pref <= n; pref++) {
        ok[(1 << n) - (1 << pref)] = true;
    }

    int ans = 0;

    for(int conf = 0; conf < (1 << n); conf++) {
        ans += ok[state[conf]];
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
