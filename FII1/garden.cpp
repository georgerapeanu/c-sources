#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 300;
const long long inf = 1LL << 56;

struct point_t {
    int x,y;

    point_t(int x = 0,int y = 0) {
        this->x = x;
        this->y = y;
    }

    bool operator < (const point_t &other)const {
        if(x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

int n,m;
int cnt[NMAX + 5][NMAX + 5];///i < j

point_t v[NMAX + 5];

point_t piv;

long long det(point_t a,point_t b,point_t c) {
    return (1LL * a.x * b.y + 1LL * b.x * c.y + 1LL * c.x * a.y) -
           (1LL * a.x * c.y + 1LL * b.x * a.y + 1LL * c.x * b.y);
}

int points_in_tri(int i,int j,int k) {

    int scad = 0;

    if(j && v[j - 1].x == v[j].x) {
        scad = 1;
    }

    if(det(v[i],v[k],v[j]) > 0) {
        return cnt[i][j] + cnt[j][k] - cnt[i][k] - scad;
    }
    else {
        return cnt[i][k] - cnt[i][j] - cnt[j][k] - 1 + scad;
    }
}

long long mi1[NMAX + 5];
long long mi2[NMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&v[i].x,&v[i].y);
    }

    long long ans = inf;

    sort(v + 1,v + 1 + n);

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            cnt[i][j] = 0;
            for(int k = 1; k <= n; k++) {
                if(v[k].x >= v[i].x && v[k].x <= v[j].x && det(v[i],v[j],v[k]) < 0) {
                    cnt[i][j]++;
                    cnt[j][i]++;
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            for(int k = 0; k <= m; k++) {
                mi1[k] = inf;
                mi2[k] = inf;
            }

            for(int k = 1; k < i; k++) {
                long long a = det(v[i],v[j],v[k]);
                int tmp = points_in_tri(k,i,j);

                if(a < 0) {
                    mi1[tmp] = min(mi1[tmp],-a);
                }
                else if(a > 0) {
                    mi2[tmp] = min(mi2[tmp],a);
                }
            }

            for(int k = i + 1; k <= j - 1; k++) {
                long long a = det(v[i],v[j],v[k]);
                int tmp = points_in_tri(i,k,j);

                if(a < 0) {
                    mi1[tmp] = min(mi1[tmp],-a);
                }
                else if(a > 0) {
                    mi2[tmp] = min(mi2[tmp],a);
                }
            }

            for(int k = j + 1; k <= n; k++) {
                long long a = det(v[i],v[j],v[k]);
                int tmp = points_in_tri(i,j,k);

                if(a < 0) {
                    mi1[tmp] = min(mi1[tmp],-a);
                }
                else if(a > 0) {
                    mi2[tmp] = min(mi2[tmp],a);
                }
            }

            for(int k = 0; k <= m; k++) {
                if(mi1[k] + mi2[m - k] < ans) {
                    ans = mi1[k] + mi2[m - k];
                }
            }
        }
    }

    printf("%.1f",(double)ans / 2);

    return 0;
}

