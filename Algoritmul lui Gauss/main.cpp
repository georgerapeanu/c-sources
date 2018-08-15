#include <cstdio>
#include <algorithm>
#define EPS 1e-10
using namespace std;
FILE *f=fopen("gauss.in","r");
FILE *g=fopen("gauss.out","w");
double V[304][304],a;
double X[304];
int N,M;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M+1;j++)
            fscanf(f,"%lf",&V[i][j]);
    int i=1,j=1;
    while(i<=N&&j<=M)
    {
        int k;
        for(k=i;k<=N;k++)
        {
            if(V[k][j]<-EPS||V[k][j]>EPS)
                break;
        }
        if(k==N+1)
        {
            j++;
            continue;
        }
        for(int l=1;l<=M+1;l++)
        {
            swap(V[i][l],V[k][l]);
        }
        for(int l=1;l<=M+1;l++)
        {
            if(l!=j)V[i][l]/=V[i][j];
        }
        V[i][j]=1;
        for(k=i+1;k<=N;k++)
        {
            for(int l=1;l<=M+1;l++)
                if(l!=j)V[k][l]-=V[i][l]*V[k][j];
            V[k][j]=0;
        }
        i++;j++;
    }
    for(int i=N;i;i--)
    {
        for(int j=1;j<=M+1;j++)
        {
            if(V[i][j]<-EPS||V[i][j]>EPS)
            {
                if(j==M+1)
                {
                    fprintf(g,"Imposibil");
                    return 0;
                }
                X[j]=V[i][M+1];
                for(int l=M;l>i;l--)
                    X[j]-=V[i][l]*X[l];
                break;
            }
        }
    }
    for(int i=1;i<=M;i++)
        fprintf(g,"%.10f ",X[i]);
    fclose(f);
    fclose(g);
    return 0;
}
