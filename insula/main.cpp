#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("insula.in","r");
FILE *g=fopen("insula.out","w");
double rez;
int R,T;
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d",&R);
        double sol = 1.0 / (sqrt(R * 1.0 * R + 1.0));
        fprintf(g,"%.3f\n",(double)((long long)(sol * 1000.0) / 1000.0));
        T--;
    }
    fclose(f);
    fclose(g);
    //printf("%.3f",0.0999);
    return 0;
}
