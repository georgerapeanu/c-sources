#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

FILE *f = fopen("pisica.in","r");
FILE *g = fopen("pisica.out","w");

struct point_t {
    double x,y;
};

const int NMAX = 1e5;
const int LGMAX = 17;

int n;
point_t v[2 * NMAX + 5];
int nxt[LGMAX + 1][2 * NMAX + 5];

inline double det(const point_t &a,const point_t &b,const point_t &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

inline double get_area(const point_t &a,const point_t &b,const point_t &c) {
    return fabs(det(a,b,c));
}

inline double dist_d_to_p(const point_t &da,const point_t &db,const point_t &p) {
    double a = db.y - da.y;
    double b = da.x - db.x;
    double c = db.x * da.y - da.x * db.y;

    return abs((a * p.x + b * p.y + c) / sqrt(a * a + b * b));
}

inline double sqr_dist_p_to_p(const point_t &a,const point_t &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double get_diameter() {
    int p = 1;
    double curr_area = 0;
    double ans = 1e18;
    for(int i = 1; i <= n; i++) {
        int nxt = i % n + 1;
        curr_area = get_area(v[i],v[nxt],v[p]);
        while(curr_area <= get_area(v[i],v[nxt],v[p % n + 1])) {
            p = p % n + 1;
            curr_area = get_area(v[i],v[nxt],v[p]);
        }
        ans = min(ans,dist_d_to_p(v[i],v[nxt],v[p]));
    }
    return ans;
}

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%lf %lf",&v[i].x,&v[i].y);
    }

    double d = get_diameter();

    d *= d;

    fscanf(f,"%d",&n);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%lf %lf",&v[i].x,&v[i].y);
        v[i + n] = v[i];
    }

    int p = 1;

    for(int i = 1; i <= 2 * n; i++) {
        while(p < 2 * n && sqr_dist_p_to_p(v[i],v[p + 1]) <= d) {
            p++;
        }
        nxt[0][i] = p;
    }

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= 2 * n; i++) {
            nxt[h][i] = nxt[h - 1][nxt[h - 1][i]];
        }
    }

    int ans = n;
    for(int i = 1; i <= n; i++) {
        int pos = i,tmp_ans = 0;
        for(int h = LGMAX; h >= 0; h--) {
            if(nxt[h][pos] < i + n) {
                pos = nxt[h][pos];
                tmp_ans |= (1 << h);
            }
        }
        ans = min(ans,tmp_ans + 1);
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
