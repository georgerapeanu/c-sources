#include <cstdio>
using namespace std;
FILE *f,*g;
char c[200];
long n,m,i,coo,val;
double minim,vot[201];
int verificare(char *p)
{
    int nrplus=0;
    for(int i=0;i<n&&nrplus<=1;i++)
    {
        if(p[i]=='+'){coo=i+1;nrplus++;}
    }
    if(nrplus==2)
    return 0;
    return 1;
}
int main()
{
    f=fopen("vot2.in","r");
    g=fopen("vot2.out","w");
    fscanf(f,"%ld %ld",&n,&m);
    for(i=1;i<=m;i++)
    {
        fscanf(f,"%s",&c);
        if(verificare(c)==1)
        {
            vot[coo]++;
            val++;
        }
    }
    minim=double(val)/5;
    for(i=1;i<=n;i++)
    {
        if(vot[i]>=minim)
        fprintf(g,"%ld ",i);
    }
    fclose(f);
    fclose(g);
    return 0;
}
