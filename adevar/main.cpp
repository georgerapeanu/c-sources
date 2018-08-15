#include <cstdio>
using namespace std;
FILE *f=fopen("adevar.in","r");
FILE *g=fopen("adevar.out","w");
long long i,j,a,c;
long long N;
long long A[21][21];
long long B[21][21];
bool ok,tmpok;
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&A[i][0]);
        for(j=1;j<=A[i][0];j++)
            fscanf(f,"%lld",&A[i][j]);
        fscanf(f,"%lld",&B[i][0]);
        for(j=1;j<=B[i][0];j++)
            fscanf(f,"%lld",&B[i][j]);
    }
    for(a=0;a<1<<(N+1)&&!ok;a+=2)
    {
        ok=1;
        for(c=1;c<=N&&ok;c++)
        {
            if(a&(1<<c))
            {
                for(i=1;i<=A[c][0]&&ok;i++)
                {
                    if(!(a&(1<<A[c][i])))
                        ok=0;
                }
                for(i=1;i<=B[c][0]&&ok;i++)
                {
                    if(a&(1<<B[c][i]))
                        ok=0;
                }
            }
            else
            {
                tmpok=1;
                for(i=1;i<=A[c][0]&&tmpok;i++)
                {
                    if(!(a&(1<<A[c][i])))
                        tmpok=0;
                }
                for(i=1;i<=B[c][0]&&tmpok;i++)
                {
                    if(a&(1<<B[c][i]))
                        tmpok=0;
                }
                ok=ok&(!tmpok);
            }
        }
        if(ok==1)
        {
            for(i=1;i<=N;i++)
            {
                if(a&(1<<i))
                    fprintf(g,"0\n");
                else
                    fprintf(g,"1\n");
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
