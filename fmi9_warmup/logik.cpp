#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("logik.in","r");
FILE *g = fopen("logik.out","w");

const int NMAX = 2e5;

int n;
int v[NMAX + 5];

inline bool ok_subsequence(const int &l,const int &r) {
    if(r - l > 0) {
        return true;
    }
    if(r - l < 0) {
        return false;
    }
    return !(v[l] & 1);
}

const int LEN = 1 << 13;
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

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int main() {

    n = i32();

    for(int i = 1; i <= n; i++) {
        v[i] = i32();
    }

    if(ok_subsequence(1,n) == false) {
        fprintf(g,"-1\n");
        return 0;
    }

    int ans = 0;

    for(int h = 0; h <= 30; h++) {
        int lst = 0;
        bool ok = true;
        for(int i = 1; i <= n; i++) {
            if((v[i] >> h) & 1) {
                ok &= (ok_subsequence(lst + 1,i - 1) == false);
                lst = i;
            }
        }
        ok &= (ok_subsequence(lst + 1,n) == false);

        if(ok) {
            ans |= (1 << h);
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
