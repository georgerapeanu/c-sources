#include <cstdio>
using namespace std;
FILE *f=fopen("efort.in","r");
FILE *g=fopen("efort.out","w");
long long E,fo,ff,j,tmp;
int K,N,i,upopas;
long long D[1001];
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&D[i]);
        D[i]+=D[i-1];
    }
    j=0;
    fo=ff=1;
    for(i=1;i<=D[N];i++)
    {
        if(i-upopas<=K)
            E++;
        else
        {
            E+=fo+ff;
            tmp=fo;
            fo=ff;
            ff=tmp+fo;
        }
        if(i>=D[j+1])
            j++;
        if(i-upopas>=K&&i==D[j])
        {upopas=D[j];fo=ff=1;}
    }
    fprintf(g,"%lld",E);
    fclose(f);
    fclose(g);
    return 0;
}
