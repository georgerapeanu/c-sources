#include <cstdio>
using namespace std;
FILE *f=fopen("betasah.in","r");
FILE *g=fopen("betasah.out","w");
int i,j,m[1005][1005],N,x[105],y[105],x1,y1,a,b,nr,D,K;
const int dirx[]={-1,-1,0,1,1,1,0,-1};
const int diry[]={0,1,1,1,0,-1,-1,-1};
int main()
{
    fscanf(f,"%d %d %d",&N,&D,&K);
    for(i=0;i<=N+1;i++)
        m[i][0]=m[i][i+1]=m[i][i+2]=m[N+1][i]=-1;
    m[0][0]=-1;
    for(i=1;i<=D;i++)
    {
        fscanf(f,"%d %d",&x[i],&y[i]);
    }
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d %d",&x1,&y1);
        m[x1][y1]=-1;
    }
   for(i=1;i<=D;i++)
    {
        for(j=0;j<8;j++)
        {
            x1=x[i];
            y1=y[i];
        while(m[x1][y1]!=-1)
           {
                m[x1][y1]=1;
               x1+=dirx[j];
                y1+=diry[j];
            }

      }
    }
    for(i=1;i<=N;i++)
    {
        nr=0;
        for(j=1;j<=i;j++)
        {
            if(m[i][j]!=-1)
                {nr++;}
            if(m[i][j]==1)
               b++;
        }
        if(nr>a)
           a=nr;
    }
    fprintf(g,"%d\n%d",a,b-D);
    fclose(f);
    fclose(g);
    return 0;
}
