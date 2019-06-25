#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("eq.in","r");
FILE *g = fopen("eq.ok","w");

const int NMAX = 1e5 + 1;
const int MMAX = 13e4 + 1;

int n,m;
int x[NMAX + 5];
int y[NMAX + 5];
int z[NMAX + 5];

int main(){

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&x[i]);
    }

    while(m--){
        int st,dr;
        fscanf(f,"%d %d",&st,&dr);

        int ma = 0;
        int mi = 1 << 28;

        for(int i = dr;i >= st;i--){
            mi = min(mi,x[i]);
            ma = max(ma,x[i]);
            y[i] = x[i] + ma - mi;
            z[i] = x[i] + mi - ma;
        }

        ma = 0;
        mi = 1 << 28;

        for(int i = st;i <= dr;i++){
            ma = max(ma,y[i]);             
            mi = min(mi,z[i]);             
        }

        fprintf(g,"%d\n",mi + ma);
    }

    fclose(f);
    fclose(g);

    return 0;
}
