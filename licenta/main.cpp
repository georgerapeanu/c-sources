#include <cstdio>
#include <vector>
#include <algorithm>
#define mp make_pair
#define pb push_back
#define x first
#define y second
using namespace std;
FILE *f=fopen("licenta.in","r");
FILE *g=fopen("licenta.out","w");
int K,act;
int N,M;
vector<pair<int,int> > E;
int main()
{
    fscanf(f,"%d",&K);
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        int X,Y;
        fscanf(f,"%d%d",&X,&Y);
        E.pb(mp(X,1));
        E.pb(mp(Y,-1));
    }
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        int X,Y;
        fscanf(f,"%d%d",&X,&Y);
        E.pb(mp(X,1));
        E.pb(mp(Y,-1));
    }
    sort(E.begin(),E.end());
    int l=0;
    for(auto it:E)
    {
        if(it.y==1)
        {
            act++;
            l=it.x;
        }
        else
        {
            if(act==2&&it.x-l>=K)
            {
                fprintf(g,"%d %d",l,l+K);return 0;
            }
            act--;
        }
    }
    fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
