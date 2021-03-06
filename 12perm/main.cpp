#include <cstdio>
#define MOD 1048576
using namespace std;
FILE *f=fopen("12perm.in","r");
FILE *g=fopen("12perm.out","w");
int T[5]={0,1,2,6,12},i,N;
int main()
{
    fscanf(f,"%d",&N);
    if(N<=4)
        {fprintf(g,"%d",T[N]);return 0;}
    i=4;
    while(i<N)
    {
        T[0]=T[1];
        T[1]=T[2];
        T[2]=T[3];
        T[3]=T[4];
        T[4]=((T[3]+T[1])%MOD+2*(i-1))%MOD;
        i++;
    }
    fprintf(g,"%d",T[4]);
    fclose(f);
    fclose(g);
    return 0;
}
