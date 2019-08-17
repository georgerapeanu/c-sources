#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

FILE *f = fopen("niciomare.in","r");
FILE *g = fopen("niciomare.out","w");

const int NMAX = 1e5;
const int KMAX = 100;
const int SMAX = 1e8;

int n,k,s;
int v[NMAX + 5];
int rightmost[NMAX + 5];
long long pref_sum[NMAX + 5];
long long dp[NMAX + 5];

struct node_t {
    long long a;
    long long b;
} aint[4 * NMAX + 5];

void build(int nod,int st,int dr) {
    aint[nod].a = 0;
    aint[nod].b = -1e18;

    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
}

void update(int nod,int st,int dr,int S,int D,long long a,long long b) {
    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        if(aint[nod].a == a) {
            if(aint[nod].b < b) {
                aint[nod].b = b;
            }
            return ;
        }
        long double x = (aint[nod].b - b) / (a - aint[nod].a);
        if(x < pref_sum[st] || x > pref_sum[dr]) {
            if(a * pref_sum[st] + b > aint[nod].a * pref_sum[st] + aint[nod].b) {
                aint[nod] = {a,b};
            }
            return ;
        }
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,a,b);
    update(nod * 2 + 1,mid + 1,dr,S,D,a,b);
}

long long query(int nod,int st,int dr,int pos) {
    if(dr < pos || st > pos) {
        return -1e18;
    }

    if(st == dr) {
        return aint[nod].a * pref_sum[pos] + aint[nod].b;
    }

    int mid = (st + dr) / 2;

    return max(aint[nod].a * pref_sum[pos] + aint[nod].b,max(query(nod * 2,st,mid,pos),query(nod * 2 + 1,mid + 1,dr,pos)));
}

int main() {

    fscanf(f,"%d %d %d",&n,&k,&s);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        pref_sum[i] = v[i] + pref_sum[i - 1];
    }

    for(int i = 0; i <= n; i++) {
        rightmost[i] = max(rightmost[i - 1],i);

        while(rightmost[i] < n && pref_sum[rightmost[i] + 1] - pref_sum[i] <= s) {
            rightmost[i]++;
        }
    }

    for(int h = 1; h <= k; h++) {
        deque<pair<long long,long long> > lines;
        lines.push_back({0,0});
        printf("stage %d:\n",k);
        for(int i = 1; i <= n; i++) {
            pair<long long,long long> tmp = {-2 * pref_sum[i],dp[i] + pref_sum[i] * pref_sum[i]};
            dp[i] = max(dp[i],dp[i - 1]);
            printf("%d:\n",i);
            while(pref_sum[i] + lines.front().first / 2 > s) {
                lines.pop_front();
            }
            for(int k = 0; k < (int)lines.size(); k++) {
                printf("%d %lld %lld\n",k,lines[k].first,lines[k].second);
                dp[i] = max(dp[i],lines[k].first * pref_sum[i] + lines[k].second + pref_sum[i] * pref_sum[i]);
            }
            lines.push_back(tmp);
        }
    }

    fprintf(g,"%lld\n",dp[n]);

    fclose(f);
    fclose(g);

    return 0;
}
///long long is not enogut if it doesn't work
