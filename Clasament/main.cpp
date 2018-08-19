#include <cstdio>
#define MOD 666013
using namespace std;
FILE *f=fopen("clasament.in","r");
FILE *g=fopen("clasament.out","w");
int rez=1;
int val;
int N,J;
int fr[100005];
int main()
{
    fscanf(f,"%d%d",&N,&J);
    fr[0]=J;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        rez=(1LL*rez*(fr[val-1]-fr[val]))%MOD;
        fr[val]++;
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
