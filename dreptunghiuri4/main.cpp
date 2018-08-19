#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <set>
#define x first.first
#define y first.second
#define dx second.first
#define dy second.second
using namespace std;
FILE *f=fopen("dreptunghiuri4.in","r");
FILE *g=fopen("dreptunghiuri4.out","w");
int M[2005][2005],N,K,nrx,nry;
long long nr;
int ctr;
unordered_map <int,int> MX,MY,IX,IY;
pair<pair<int,int>,pair<int,int> > V[2005];
set<int> X,Y;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d%d%d",&V[i].x,&V[i].y,&V[i].dx,&V[i].dy);
        X.insert(V[i].x);
        X.insert(V[i].dx);
        Y.insert(V[i].y);
        Y.insert(V[i].dy);
    }
    ctr=1;
    for(auto it:X)
    {
        MX[it]=ctr;
        IX[ctr]=it;
        ctr++;
    }
    ctr=1;
    for(auto it:Y)
    {
        MY[it]=ctr;
        IY[ctr]=it;
        ctr++;
    }
    for(int i=1;i<=N;i++)
    {
        M[MX[V[i].x]][MY[V[i].y]]++;
        M[MX[V[i].dx]][MY[V[i].y]]--;
        M[MX[V[i].x]][MY[V[i].dy]]--;
        M[MX[V[i].dx]][MY[V[i].dy]]++;
    }
    nrx=MX.size();
    nry=MY.size();
    for(int i=1;i<nrx;i++)
    {
        for(int j=1;j<nry;j++)
        {
            M[i][j]+=M[i-1][j]+M[i][j-1]-M[i-1][j-1];
            if(M[i][j]==K)
            {
                long long x1,x2,y1,y2;
                x1=IX[i];
                x2=IX[i+1];
                y1=IY[j];
                y2=IY[j+1];
                nr+=(x2-x1)*(y2-y1);
            }
        }
    }
    fprintf(g,"%lld",nr);
    fclose(f);
    fclose(g);
    return 0;
}
