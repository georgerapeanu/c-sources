#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

FILE *f = fopen("unique.in","r");
FILE *g = fopen("unique.out","w");

const int NMAX = 1e5;

int t;
int n;
int v[NMAX + 5];

const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN) {
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }
    return ans;
}

int ans = 0;
int fr[NMAX + 5];

void solve(int st,int dr) {
    if(st == dr) {
        if(v[st] == 1) {
            ans = max(ans,1);
        }
        return ;
    }

    int mid = (st + dr) / 2;

    solve(st,mid);
    solve(mid + 1,dr);

    int l = mid + 1;
    int r = mid;
    int mex = 1;
    int ma = 0;

    while(l > st || r < dr) {

        if(l > st && (r == dr || v[l - 1] < v[r + 1])) {
            fr[v[--l]]++;
            ma = max(ma,v[l]);
        }

        else {
            fr[v[++r]]++;
            ma = max(ma,v[r]);
        }

        while(fr[mex]) {
            mex++;
        }

        if(ma < mex) {
            ans = max(ans,r - l + 1);
        }
    }

    for(int i = st; i <= dr; i++) {
        fr[v[i]] = 0;
    }
}

int main() {

    t = i32();

    while(t--) {
        n = i32();

        for(int i = 1; i <= n; i++) {
            v[i] = i32();
        }

        ans = 0;

        solve(1,n);

        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
