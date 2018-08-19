#include <cstdio>
using namespace std;
FILE *f=fopen("patrat.in","r");
FILE *g=fopen("patrat.out","w");
int N,M,i,j,v[300][300],a,b,c,l;
bool B[300][300];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&v[i][j]);
        }
    }
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            if(v[i][j]>v[i-1][j]&&v[i][j]>v[i-1][j-1]&&v[i][j]>v[i][j-1]&&v[i][j]>v[i+1][j-1]&&v[i][j]>v[i+1][j]&&v[i][j]>v[i+1][j+1]&&v[i][j]>v[i][j+1]&&v[i][j]>v[i-1][j+1])
                {B[i][j]=1;a++;}
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            if(B[i][j])
            for(l=2;l+i-1<=N&&l+j-1<=M;l++)
                    if(B[i][j]&B[i+l-1][j]&B[i+l-1][j+l-1]&B[i][j+l-1])
                    {
                        b++;
                        if(l>c)
                            c=l;
                    }
    fprintf(g,"%d\n%d\n%d",a,b,c);
    fclose(f);
    fclose(g);
    return 0;
}
