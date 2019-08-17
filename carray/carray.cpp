#include <cstdio>

using namespace std;

FILE *f = fopen("carray.in","r");
FILE *g = fopen("carray.out","w");

const int NMAX = 2e4;
const int MMAX = 5e5;
const int QMAX = 2e4;
const int LGMAX = 18;

int n,m,q;
int v[NMAX + 5];

long long weight[MMAX + NMAX + 5];
int low_child[MMAX + NMAX + 5];
long long heavy_jump_pref[MMAX + NMAX + 1];
int heavy_child[LGMAX + 1][MMAX + NMAX + 1];
int l[MMAX + NMAX + 5];
int r[MMAX + NMAX + 5];
int top[MMAX + NMAX + 5];

const int LEN = 1 << 15;
int ind = LEN - 1;
char buff[LEN];

template<typename tp>
tp read() {
    tp ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    return ans;
}

int main() {

    n = read<int>();
    m = read<int>();
    q = read<int>();

    for(int i = 1; i <= n; i++) {
        v[i] = read<int>();
        weight[i] = 1;
    }

    for(int i = n + 1; i <= n + m; i++) {
        int x,y;
        x = read<int>();
        y = read<int>();
        l[i] = x;
        r[i] = y;
        weight[i] = weight[x] + weight[y];
        if(weight[x] > weight[y]) {
            low_child[i] = y;
            heavy_jump_pref[i] = 0 + heavy_jump_pref[x];
            heavy_child[0][i] = x;
        }
        else {
            low_child[i] = x;
            heavy_jump_pref[i] = weight[x] + heavy_jump_pref[y];
            heavy_child[0][i] = y;
        }
        for(int h = 1; h <= LGMAX; h++) {
            heavy_child[h][i] = heavy_child[h - 1][heavy_child[h - 1][i]];
            top[i] = h;
            if(heavy_child[h][i] == 0) {
                break;
            }
        }
    }

    for(int i = 1; i <= q; i++) {
        int nod;
        long long pos;
        nod = read<int>();
        pos = read<long long>();
        while(nod > n) {
            for(int h = top[nod]; h >= 0; h--) {
                int to = heavy_child[h][nod];
                if(to != 0 && heavy_jump_pref[nod] - heavy_jump_pref[to] < pos && pos <= heavy_jump_pref[nod] - heavy_jump_pref[to] + weight[to]) {
                    pos -= (heavy_jump_pref[nod] - heavy_jump_pref[to]);
                    nod = to;
                }
            }
            if(nod <= n) {
                break;
            }
            if(low_child[nod] == l[nod]) {
                nod = l[nod];
            }
            else {
                pos -= weight[l[nod]];
                nod = r[nod];
            }
        }

        fprintf(g,"%d\n",v[nod]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
