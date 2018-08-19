#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("fillmat.in","r");
FILE *g=fopen("fillmat.out","w");
char c[305][305],n[305][305];
int N,nr,j,i;
bool progres=1;
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
       {fgets(c[i]+1,305,f);strcpy(n[i]+1,c[i]+1);}
       for(i=0;i<=N+1;i++)
         n[i][0]=n[i][N+1]=n[0][i]=n[N+1][i]=c[i][0]=c[i][N+1]=c[0][i]=c[N+1][i]='0';
    progres=1;
    while(progres)
    {
        progres=0;
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                if(c[i][j]!='1')
                {
                    if(n[i-1][j]+n[i-1][j+1]+n[i][j+1]+n[i+1][j+1]+n[i+1][j]+n[i+1][j-1]+n[i][j-1]+n[i-1][j-1]-8*'0'>=3)
                    {
                        progres=1;
                        c[i][j]='1';
                    }
                }
            }
        }
        for(j=1;j<=N;j++)
                strcpy(n[j],c[j]);
        nr++;
    }
    fprintf(g,"%d",nr-1);
    fclose(f);
    fclose(g);
    return 0;
}
