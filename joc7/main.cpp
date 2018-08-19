#include <fstream>
#include <iostream>
using namespace std;
ifstream f("joc7.in");
ofstream g("joc7.out");
char c[32][32],a[32][32];
int v[26],m,n,i,j,x,y,nrpasi,nrmaximpasi;
int pasi(int x, int y)
{
    if(v[c[x][y]-'a']==0)
    {
        v[c[x][y]-'a']=1;
     nrpasi++;
     if(nrpasi>nrmaximpasi)
        {
            nrmaximpasi=nrpasi;

       }
                pasi(x,y+1);
                pasi(x+1,y);
                pasi(x,y-1);
                pasi(x-1,y);
         v[c[x][y]-'a']=0;
         nrpasi--;
    }
    return 0;
}
int main()
{
    f>>n>>m;
    if (n>26) n=26;
 for(i=1;i<=n;i++)
 {
     for(j=1;j<=m;j++)
     {
         f>>a[i][j];
     }
 }
 if (n>26) n=26;
 if (m>26) m=26;
 for(i=1;i<=n;i++)
 {
     for(j=1;j<=m;j++)
     {
         c[i][j]=a[i][j];
     }
 }

 for(i=0;i<=n+1;i++)
    {
        c[i][0]=c[1][1];
        c[i][m+1]=c[1][1];
    }
    for(j=0;j<=m+1;j++)
    {
        c[0][j]=c[1][1];
        c[n+1][j]=c[1][1];
    }
     for(i=0;i<=n+1;i++)
 {
     for(j=0;j<=m+1;j++)
     {
        cout<<c[i][j];
     }
     cout<<"\n";
 }
    pasi(1,1);
    g<<nrmaximpasi;
    return 0;
}
