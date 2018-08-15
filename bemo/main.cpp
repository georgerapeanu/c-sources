#include <cstdio>
#include <fstream>
#include <algorithm>
#define mp make_pair
#define zeros(x) x&(x^(x-1))
using namespace std;
FILE *f=fopen("bemo.in","r");
FILE *g=fopen("bemo.out","w");
int V[1501][1501];
pair<int,int> poz[1500*1500+1];
bool ok[1501][1501];
int N,M;
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
            {fscanf(f,"%d",&V[i][j]);poz[V[i][j]]=mp(i,j);}
    }
    int nr=1;
    for(int i=1;i<N+M;i++)
    {
        while(ok[poz[nr].first][poz[nr].second])
            nr++;
        for(int lin=poz[nr].first-1;lin;lin--)
        {
            for(int col=poz[nr].second+1;col<=M;col++)
            {
                if(ok[lin][col])
                break;
                ok[lin][col]=1;
            }
        }
        for(int lin=poz[nr].first+1;lin<=N;lin++)
        {
            for(int col=poz[nr].second-1;col;col--)
            {
                if(ok[lin][col])
                break;
                ok[lin][col]=1;
            }
        }
        nr++;
    }
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(!ok[i][j])
                fprintf(g,"%d ",V[i][j]);
    fclose(f);
    fclose(g);
    return 0;
}
