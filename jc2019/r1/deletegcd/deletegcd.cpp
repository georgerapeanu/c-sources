#include <cstdio>
#include <cstring>

using namespace std;

FILE *f = fopen("deletegcd.in","r");
FILE *g = fopen("deletegcd.out","w");

const int LEN = 1e4;
const int NMAX = 1e6;
const int VMAX = 1e6;
const int SZ = 7;

char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int stuff[VMAX + 1][SZ + 1];
int len[VMAX + 1];

int n,q;
int v[NMAX + 1];
int fst_without[NMAX + 1][SZ + 1];

int main() {

    for(int i = 2; i <= VMAX; i++) {
        if(len[i] == 0) {
            for(int x = i; x <= VMAX; x += i) {
                stuff[x][++len[x]] = i;
            }
        }
    }

    n = i32();
    q = i32();

    for(int i = 1; i <= n; i++) {
        v[i] = i32();
    }

    for(int i = n; i; i--) {
        for(int x = 1; x <= len[v[i]]; x++) {
            int pos = -1;
            for(int j = 1; j <= len[v[i + 1]]; j++) {
                if(stuff[v[i + 1]][j] == stuff[v[i]][x]) {
                    pos = j;
                    break;
                }
            }
            if(pos != -1) {
                fst_without[i][x] = fst_without[i + 1][pos];
            }
            else {
                fst_without[i][x] = i + 1;
            }
        }
    }

    while(q--) {
        int l,r;
        l = i32();
        r = i32();

        bool ok = false;

        for(int x = 1; x <= len[v[l + 1]]; x++) {
            if(fst_without[l + 1][x] > r) {
                ok = true;
                break;
            }
        }

        for(int x = 1; x <= len[v[l]]; x++) {
            if(fst_without[l][x] >= r) {
                ok = true;
                break;
            }

            int y = fst_without[l][x] + 1;
            int p = -1;
            for(int tmp = 1; tmp <= len[v[y]]; tmp++) {
                if(stuff[v[y]][tmp] == stuff[v[l]][x]) {
                    p = tmp;
                    break;
                }
            }
            if(p != -1 && fst_without[y][p] > r) {
                ok = true;
                break;
            }
        }

        fputc('0' + ok,g);
    }

    fclose(f);
    fclose(g);

    return 0;
}
