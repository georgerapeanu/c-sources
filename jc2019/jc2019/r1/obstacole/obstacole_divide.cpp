#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("obstacole.in","r");
FILE *g = fopen("obstacole.out","w");

struct segm_t {
    int x,y,xx,yy;
};

const int NMAX = 1e5;
const int MMAX = 1e5;
const int XMAX = 1e9 + 1e4;

int n,m;
segm_t segm[NMAX + 5];
int x[2 * NMAX + 5];
int y[2 * NMAX + 5];
int fa[2 * NMAX + 5];

int get_root(int a) {
    if(fa[a] == -1) {
        return a;
    }
    return fa[a] = get_root(fa[a]);
}

int point_id[2 * NMAX + 5];
int line_id[2 * NMAX + 5];

int pivot_x;

bool cmp_line(int a,int b) {
    int ca = (segm[a].xx < pivot_x ? 0:(segm[a].x <= pivot_x ? 1:2));
    int cb = (segm[b].xx < pivot_x ? 0:(segm[b].x <= pivot_x ? 1:2));

    return ca < cb;
}

bool cmp_point(int a,int b) {
    return x[a] < x[b];
}

bool cmp_combined(int a,int b) {
    if(a < 0 && b < 0) {
        a *= -1;
        b *= -1;
        return (double(pivot_x - segm[a].x) / double(segm[a].xx - segm[a].x)) * (segm[a].yy - segm[a].y) + segm[a].y <
               (double(pivot_x - segm[b].x) / double(segm[b].xx - segm[b].x)) * (segm[b].yy - segm[b].y) + segm[b].y;
    }
    else if(a > 0 && b > 0) {
        return y[a] < y[b];
    }
    else if(a < 0 && b > 0) {
        a *= -1;
        return 1LL * y[b] * (segm[a].xx - segm[a].x) > 1LL * (segm[a].yy - segm[a].y) * (pivot_x - segm[a].x) + 1LL * segm[a].y * (segm[a].xx - segm[a].x);
    }
    else if(a > 0 && b < 0) {
        b *= -1;
        return 1LL * y[a] * (segm[b].xx - segm[b].x) <= 1LL * (segm[b].yy - segm[b].y) * (pivot_x - segm[b].x) + 1LL * segm[b].y * (segm[b].xx - segm[b].x);
    }
}

int tmp_solve[4 * NMAX + 5],len;
void solve(int p_st,int p_dr,int l_st,int l_dr) {
    if(p_dr < p_st) {
        return ;
    }

    int a,b;
    a = b = (p_st + p_dr) / 2;

    while(a > p_st && x[point_id[a - 1]] == x[point_id[a]]) {
        a--;
    }
    while(b < p_dr && x[point_id[b + 1]] == x[point_id[b]]) {
        b++;
    }

    pivot_x = x[point_id[a]];

    sort(line_id + l_st,line_id + l_dr + 1,cmp_line);

    int c = l_st - 1,d = l_dr + 1;

    for(int i = l_st; i <= l_dr; i++) {
        if(segm[line_id[i]].xx < pivot_x) {
            c = i;
        }
        else if(segm[line_id[i]].x > pivot_x && d == l_dr + 1) {
            d = i;
        }
    }

    ///solve points [a,b] with lines of (c + 1,d - 1) at point pivot_x
    if(c + 1 <= d - 1) {
        len = 0;
        for(int i = a; i <= b; i++) {
            tmp_solve[++len] = point_id[i];
        }
        for(int i = c + 1; i <= d - 1; i++) {
            if(segm[line_id[i]].y > segm[line_id[i]].yy) {
                if(segm[line_id[i]].x != pivot_x) {
                    tmp_solve[++len] = -line_id[i];
                }
            }
            else {
                if(segm[line_id[i]].xx != pivot_x) {
                    tmp_solve[++len] = -line_id[i];
                }
            }
        }

        sort(tmp_solve + 1,tmp_solve + 1 + len,cmp_combined);

        int lst = -1;

        for(int i = len; i; i--) {
            if(tmp_solve[i] > 0) {
                fa[tmp_solve[i]] = lst;
            }
            else {
                lst = -tmp_solve[i];
            }
        }
    }
    else {
        for(int i = a; i <= b; i++) {
            fa[point_id[i]] = -1;
        }
    }

    vector<int> tmp(d - 1 - c - 1+ 1,0);
    for(int i = c + 1; i <= d - 1; i++) {
        tmp[i - c - 1] = line_id[i];
    }

    solve(p_st,a - 1,l_st,d - 1);
    for(int i = c + 1; i <= d - 1; i++) {
        line_id[i] = tmp[i - c - 1];
    }
    solve(b + 1,p_dr,c + 1,l_dr);

}

const int LEN = 1 << 17;
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

int main() {

    n = i32();
    m = i32();

    for(int i = 1; i <= n; i++) {
        segm[i].x = i32();
        segm[i].y = i32();
        segm[i].xx = i32();
        segm[i].yy = i32();
        if(segm[i].x > segm[i].xx) {
            swap(segm[i].x,segm[i].xx);
            swap(segm[i].y,segm[i].yy);
        }
        if(segm[i].y > segm[i].yy) {
            x[i] = segm[i].x;
            y[i] = segm[i].y;
        }
        else {
            x[i] = segm[i].xx;
            y[i] = segm[i].yy;
        }
    }

    for(int i = 1; i <= m; i++) {
        x[i + n] = i32();
        y[i + n] = i32();
    }

    for(int i = 1; i <= n + m; i++) {
        point_id[i] = i;
        line_id[i] = i;
    }

    sort(point_id + 1,point_id + 1 + n + m,cmp_point);
    solve(1,n + m,1,n);

    for(int i = 1; i <= m; i++) {
        fprintf(g,"%d\n",x[get_root(i + n)]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
