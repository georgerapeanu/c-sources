#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("obstacole.in","r");
FILE *g = fopen("obstacole.ok","w");

struct segm_t {
    int x,y,xx,yy;
};

const int NMAX = 1e5;
const int MMAX = 1e5;
const int XMAX = 1e9 + 1e4;

int n,m;
segm_t segm[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d %d %d %d",&segm[i].x,&segm[i].y,&segm[i].xx,&segm[i].yy);
        if(segm[i].x > segm[i].xx) {
            swap(segm[i].x,segm[i].xx);
            swap(segm[i].y,segm[i].yy);
        }
    }

    for(int i = 1; i <= m; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        bool ok = true;
        while(ok) {
            ok = false;
            int bst_id = -1;
            double bst_y = XMAX + 1;
            for(int i = 1; i <= n; i++) {
                if(max(segm[i].y,segm[i].yy) <= y) {
                    continue;
                }
                if(segm[i].x <= x && x <= segm[i].xx) {
                    double scale = double(x - segm[i].x) / double(segm[i].xx - segm[i].x);
                    double y_sect = (segm[i].yy - segm[i].y) * scale + segm[i].y;
                    if(y_sect - y > -(1e-8)) {
                        ok = true;
                        if(bst_id == -1 || (bst_y - y_sect) > -(1e-8)) {
                            bst_y = y_sect;
                            bst_id = i;
                        }
                    }
                }
            }
            if(bst_id != -1) {
                if(segm[bst_id].y > segm[bst_id].yy) {
                    x = segm[bst_id].x;
                    y = segm[bst_id].y;
                }
                else {
                    x = segm[bst_id].xx;
                    y = segm[bst_id].yy;
                }
            }
        }
        fprintf(g,"%d\n",x);
    }

    fclose(f);
    fclose(g);

    return 0;
}
