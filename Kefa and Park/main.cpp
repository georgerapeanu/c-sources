#include <iostream>
using namespace std;
char urm[100001][100000];
int n,i,m,x,y,nr;
bool cat[100001];
void find(int v,int k)
{
    if(k>m);
    else if(urm[v][0]==0) nr++;
    else
    {
        int i;
        if(cat[v]==1)
        k++;
        for(i=1;i<=urm[v][0];i++)
        find(urm[v][i],k);
    }
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>cat[i];
    }
    for(i=1;i<n;i++)
    {
        cin>>x>>y;
        urm[x][++urm[x][0]]=y;
    }
    find(1,0);
    cout<<nr;
    return 0;
}