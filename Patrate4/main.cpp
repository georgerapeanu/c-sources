#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("patrate4.in","r");
FILE *g=fopen("patrate4.out","w");
int N,K;
int V[1030][1030];
vector<pair<pair<int,int>,int> > R;
void solve(int stx,int sty,int drx,int dry)
{
    int val=V[drx][dry]-V[stx-1][dry]-V[drx][sty-1]+V[stx-1][sty-1];
    int S=(drx-stx+1)*(dry-sty+1);
    if(!val)return ;
    if(1.0*S/K<=val&&val<4.0*S/K)
    {
        R.push_back({{stx,sty},drx-stx+1});
        return ;
    }
    int midx=(stx+drx)/2,midy=(sty+dry)/2;
    solve(stx,sty,midx,midy);
    solve(midx+1,sty,drx,midy);
    solve(stx,midy+1,midx,dry);
    solve(midx+1,midy+1,drx,dry);
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        V[x][y]=1;
    }
    for(int i=1;i<=1024;i++)
    {
        for(int j=1;j<=1024;j++)
        {
            V[i][j]+=V[i-1][j]+V[i][j-1]-V[i-1][j-1];
        }
    }
    solve(1,1,1<<10,1<<10);
    fprintf(g,"%d\n",R.size());
    for(auto it:R)
        fprintf(g,"%d %d %d\n",it.first.first,it.first.second,it.second);
    fclose(f);
    fclose(g);
    return 0;
}
