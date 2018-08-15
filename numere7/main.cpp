#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("numere7.in","r");
FILE *g=fopen("numere7.out","w");
long long nr=1,ctr,N,j;
char rez[23];
long long frecv[10];
char X[23];
long long k,i;
int main()
{
    fscanf(f,"%lld %s",&k,X+1);
    N=strlen(X+1);
    if(X[N-1]=='\n')
        N--;
    for(i=1;i<=N;i++)
    {
        nr*=i;
        frecv[X[i]-'0']++;
    }
    for(i=0;i<10;i++)
    {
        for(j=1;j<=frecv[i];j++)
            nr/=j;
    }
    while(N)
    {
        for(i=0;i<=9;i++)
        {
            if(frecv[i])
            {
                if((nr*frecv[i])/N>=k)
                {
                    rez[++ctr]='0'+i;
                    nr*=frecv[i];
                    nr/=N;
                    frecv[i]--;
                    break;
                }
                else
                {
                    k-=(nr*frecv[i])/N;
                }
            }
        }
        N--;
    }
    fputs(rez+1,g);
    fclose(f);
    fclose(g);
    return 0;
}
