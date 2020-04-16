///fuck this shit i'm out
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

FILE *f = fopen("pudge.in","r");
FILE *g = fopen("pudge.out","w");

const int NMAX = 1e5;
const int LEN = 1 << 14;
const double eps = 1e-9;
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

int x,y,d,n;

int p[NMAX + 5];
int v[NMAX + 5];

int cmp(double a,double b) {
    if(fabs(a - b) < eps) {
        return 0;
    }
    return a > b ? -1:1;
}

int main() {

    x = i32();
    y = i32();
    d = i32() / 2;
    n = i32();

    for(int i = 1; i <= n; i++) {
        p[i] = i32();
        v[i] = i32();
    }

    vector<pair<int,int> > events;

    for(int i = 1; i <= n; i++) {
        if(p[i] + 1LL * v[i] * y > x) {
            continue;
        }

        int st = -1,dr = x + 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;
            double ds = hypot(mid - x,y);
            double new_pos = p[i] + v[i] * ds;
            if(cmp(d,mid - new_pos) == 1) {
                dr = mid;
            }
            else {
                st = mid;
            }
        }

        int rgt = dr;

        st = -1;
        dr = x + 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;
            double ds = hypot(mid - x,y);
            double new_pos = p[i] + v[i] * ds;
            if(cmp(-d,mid - new_pos) >= 0) {
                dr = mid;
            }
            else {
                st = mid;
            }
        }

        int lft = dr;

        if(lft < rgt) {
            events.push_back({lft,1});
            events.push_back({rgt,-1});
        }
    }

    sort(events.begin(),events.end());

    int active = 0;
    int ans = 0;

    for(auto it:events) {
        active += it.second;
        ans = max(ans,active);
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
