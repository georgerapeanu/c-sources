#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("drum6.in","r");
FILE *g=fopen("drum6.out","w");
int N,M,i,j,ctr,x1,y1,x2,y2;
char c[1050][1050];
char rez[2100];
bool dir[1050][1050];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=0;i<=N;i++)
    fgets(c[i]+1,1050,f);
    for(i=1;i<N;i++)
        dir[i][M]=1;
    for(i=N-1;i>0;i--)
    {
        for(j=M-1;j>0;j--)
        {
            if(c[i+1][j]<c[i][j+1])
            {
                dir[i][j]=1;
            }
            else if(c[i+1][j]==c[i][j+1])
            {
                x1=i+1;x2=i;
                y1=j;y2=j+1;
                while(c[x1][y1]==c[x2][y2]&&(x1!=x2||y1!=y2)&&(x1<=N&&y1<=M)&&(x2<=N&&y2<=M))
                {
                    if(dir[x1][y1])
                        x1++;
                    else
                        y1++;
                    if(dir[x2][y2])
                        x2++;
                    else
                        y2++;
                }
                 if(c[x1][y1]<c[x2][y2])
                {
                    dir[i][j]=1;
                }
            }
        }
    }
    i=1;j=1;
    while(i!=N||j!=M)
    {
        rez[ctr++]=c[i][j];
        if(dir[i][j])
            i++;
        else
            j++;
    }
    rez[ctr]=c[N][M];
    fprintf(g,"%s",rez);
    fclose(f);
    fclose(g);
    return 0;
}
