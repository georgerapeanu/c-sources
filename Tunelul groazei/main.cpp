#include <cstdio>
#include <vector>
#define EPS (1e-6)
using namespace std;
FILE *f=fopen("tunel.in","r");
FILE *g=fopen("tunel.out","w");
double V[258][258],u=1;
int N,M;
vector<pair<int,double> > G[258];
double X[258];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        double z;
        fscanf(f,"%d %d %lf",&x,&y,&z);
        G[x].push_back({y,z});
        G[y].push_back({x,z});
    }
    for(int i=1;i<=N;i++)
    {
        for(auto it:G[i])
        {
            V[i][it.first]+=u/G[i].size();
            V[i][N+1]-=it.second/G[i].size();
        }
        V[i][i]=-1;
        V[i][N]=0;
    }
    int i=1,j=1;
    while(i<=N&&j<=N)
    {
        int k;
        for(k=i;k<=N;k++)
        {
            if(V[k][j]>EPS||V[k][j]<-EPS)break;
        }
        if(k==N+1)
        {
            j++;
            continue;
        }
        for(int l=1;l<=N+1;l++)swap(V[i][l],V[k][l]);
        for(int l=j+1;l<=N+1;l++)
        {
            V[i][l]/=V[i][j];
        }
        V[i][j]=1;
        for(int k=i+1;k<=N;k++)
        {
            for(int l=j+1;l<=N+1;l++)
                V[k][l]-=V[k][j]*V[i][l];
            V[k][j]=0;
        }
        i++;
        j++;
    }
    for(int i=N;i;i--)
    {
        for(int j=1;j<=N+1;j++)
        {
            if(V[i][j]>EPS||V[i][j]<-EPS)
            {
                X[j]=V[i][N+1];
                for(int k=j+1;k<=N;k++)
                {
                    X[j]-=X[k]*V[i][k];
                }
                break;
            }
        }
    }
    fprintf(g,"%.4f",X[1]);
    fclose(f);
    fclose(g);
    return 0;
}
