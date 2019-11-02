#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("sec.in","r");
FILE *g = fopen("sec.out","w");

const int NMAX = 2e6;

int t,c,n,k;
int h[2 * NMAX + 5];

const int LEN = 1e4;
char buff[LEN];
int ind = LEN - 1;
int st[2 * NMAX + 5],st_len;

int i32() {
    int ans = 0;
    int sgn = 1;

    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    if(buff[ind] == '-') {
        sgn = -1;
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans * sgn;
}

long long compute(int st,int dr,int n,int pos) {
    ///i = st...dr += min(i + n,pos)
    ///st <= i <= pos - n -> i + n
    ///pos - n + 1 <= i <= dr -> pos

    long long ans = 0;
    for(int i = st; i <= dr; i++) {
        ans += min(i + n,pos);
    }
    return ans;
}

long long solve(int st1,int dr1,int st2,int dr2,int val) {

    if(dr1 < st1 || dr2 < st2) {
        return 0;
    }

    long long ans = 0;

    for(int i = st1; i <= dr1; i++) {
        ans += 1LL * val * max(0,(min(i + n - 1,dr2) - max(i + k - 1,st2) + 1));
    }

    return ans;
}

int main() {

    t = i32();
    c = i32();
    c = 3 - c;

    while(t--) {
        int len;

        n = i32();
        k = i32();

        int ma = 0;

        for(int i = 1; i <= n; i++) {
            h[i] = i32();
            ma = max(ma,h[i]);
        }

        len = c * n;

        for(int i = n + 1; i <= len; i++) {
            h[i] = h[i - n];
        }

        long long ans = 0;

        h[0] = 1e6 + 5;
        h[len + 1] = 1e6 + 5;
        st_len = 0;
        for(int i = 1; i <= len + 1; i++) {
            while(st_len > 0 && h[st[st_len]] <= h[i]) {
                if(st[st_len] <= n) {
                    ans += solve(st[st_len - 1] + 1,st[st_len],st[st_len],i - 1,h[st[st_len]]);
                }
                else {
                    ans += solve(max(st[st_len - 1] + 1,st[st_len] - n + 1),n,st[st_len],i - 1,h[st[st_len]]);
                }
                st_len--;
            }
            st[++st_len] = i;
        }

        if(c == 2) {
            ans -= 1LL * ma * (n - 1);
        }

        fprintf(g,"%lld\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
