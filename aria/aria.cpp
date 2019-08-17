#include <cstdio>

using namespace std;

FILE *f = fopen("aria.in","r");
FILE *g = fopen("aria.out","w");

long double det(long double ax,long double ay,long double bx,long double by,long double cx,long double cy){
    return ax * (by - cy) + bx * (cy - ay) + cx * (ay - by);
}

int n;
long double x[int(1e5) + 5];
long double y[int(1e5) + 5];

int main(){

    long double arie = 0;

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%Lf %Lf",&x[i],&y[i]);
        if(i > 1)arie += det(0,0,x[i - 1],y[i - 1],x[i],y[i]);
    }
    
    arie += det(0,0,x[n],y[n],x[1],y[1]);

    fprintf(g,"%.6Lf",((arie < 0 ? -arie:arie) / 2));

    fclose(f);
    fclose(g);

    return 0;
}
