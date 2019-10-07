#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("oglinzi.in","r");
FILE *g = fopen("oglinzi.out","w");

const int NMAX = 200;
const int LMAX = 800;
const int inf = 1 << 28;

int t;
int n,l,h;

pair<pair<int,int>,int> v[NMAX + 5];

int dp[LMAX + 5][2],last = 0;
int tmp[2 * LMAX + 5][2];

void propag(int from,int to) {
    for(int i = 0; i <= LMAX; i++) {
        tmp[i][0] = tmp[i][1] = inf;
    }
    for(int i = 0; i <= LMAX; i++) {
        if(i + (to - from) <= LMAX) {
            tmp[i + (to - from)][0] = min(tmp[i + (to - from)][0],dp[i][0]);
        }
        if(i >= (to - from)) {
            tmp[i - (to - from)][1] = min(tmp[i - (to - from)][1],dp[i][1]);
        }
        else {
            tmp[(to - from) - i][0] = min(tmp[(to - from) - i][0],dp[i][1]);
        }
    }
    for(int i = 0; i <= LMAX; i++) {
        dp[i][0] = tmp[i][0];
        dp[i][1] = tmp[i][1];
        tmp[i][0] = tmp[i][1] = inf;
    }
}

void do_platform(int hl,int len,int hp,int bonus_cost) {
    if(hl > hp) {
        ///0 case
        tmp[hl + len][0] = min(tmp[hl + len][0],bonus_cost + dp[hl][0]);
        ///1 case
        if(hl - len >= hp) {
            tmp[hl - len][1] = min(tmp[hl - len][1],bonus_cost + dp[hl][1]);
        }
        else {
            tmp[2 * hp + len - hl][0] = min(tmp[2 * hp + len - hl][0],bonus_cost + dp[hl][1]);
        }
    }
    else if(hl == hp) {
        ///0 case
        int a = hl + len;
        int c = a / hp;
        if(c % 2 == 0) {
            tmp[a % hp][0] = min(tmp[a % hp][0],dp[hl][0] + bonus_cost);
        }
        else {
            tmp[hp - (a % hp)][1] = min(tmp[hp - (a % hp)][1],dp[hl][0] + bonus_cost);
        }
        ///1 case
        tmp[hl + len][0] = min(tmp[hl + len][0],dp[hl][1] + bonus_cost);
    }
    else {
        ///0 case
        int a = hl + len;
        int c = a / hp;
        if(c % 2 == 0) {
            tmp[a % hp][0] = min(tmp[a % hp][0],dp[hl][0] + bonus_cost);
        }
        else {
            tmp[hp - (a % hp)][1] = min(tmp[hp - (a % hp)][1],dp[hl][0] + bonus_cost);
        }
        ///1 case
        a = (hp - hl) + len;
        c = a / hp;
        if(c % 2 == 0) {
            tmp[hp - (a % hp)][1] = min(tmp[hp - (a % hp)][1],dp[hl][1] + bonus_cost);
        }
        else {
            tmp[(a % hp)][0] = min(tmp[(a % hp)][0],dp[hl][1] + bonus_cost);
        }
    }
}

int main() {

    fscanf(f,"%d",&t);

    for(int q = 1; q <= t; q++) {
        fscanf(f,"%d %d %d",&n,&l,&h);

        for(int i = 1; i <= n; i++) {
            int l,r,h;
            fscanf(f,"%d %d %d",&l,&r,&h);
            v[i] = {{l,r},h};
        }

        last = 0;

        for(int i = 0; i <= LMAX; i++) {
            dp[i][0] = dp[i][1] = inf;
        }

        dp[0][0] = 0;

        for(int i = 1; i <= n; i++) {
            for(int i = 0; i <= LMAX; i++) {
                tmp[i][0] = tmp[i][1] = inf;
            }
            propag(last,v[i].first.first);
            last = v[i].first.first;
            for(int hl = 0; hl <= LMAX; hl++) {
                do_platform(hl,v[i].first.second - v[i].first.first,v[i].second,0);
                int r = v[i].first.second;
                int l = v[i].first.first;
                for(int hp = max(1,hl - (r - l + 2)); hp <= min(LMAX,hl + (r - l + 2)); hp++) {
                    do_platform(hl,v[i].first.second - v[i].first.first,hp,abs(hp - v[i].second));
                }
            }
            for(int i = 0; i <= LMAX; i++) {
                dp[i][0] = tmp[i][0];
                dp[i][1] = tmp[i][1];
            }
            last = v[i].first.second;
        }

        propag(last,l);

        int ans = inf;
        for(int x = 0; x <= h; x++) {
            ans = min(ans,dp[x][0]);
            ans = min(ans,dp[x][1]);
        }

        if(ans == inf) {
            fprintf(g,"Imposibil\n");
        }
        else            {
            fprintf(g,"%d\n",ans);
        }
    }



    return 0;
}
