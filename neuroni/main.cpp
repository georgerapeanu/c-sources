#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("neuroni.in","r"),*g=fopen("neuroni.out","w");
bool rez[110][110];
int i,j,N,M,nr,rezultat[110],tmp;
int main(){
    fscanf(f,"%d%d",&N,&M);
    for(i=1;i<=N;i++)
    {
       for(j=1;j<=i;j++)
       {
           rez[i][j]=i%2;
       }
    }

    for(i=1;i<=M;i++)
    {
        nr=1;
        for(j=1;j<N;j++)
        {
            tmp=nr;
            nr+=rez[j][nr];
            rez[j][tmp]=(rez[j][tmp]==1 ? 0:1);
        }
        rezultat[nr]++;
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",rezultat[i]);
    fclose(f);
    fclose(g);
    return 0;
}
