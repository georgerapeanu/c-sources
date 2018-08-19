#include <fstream>
#include <cstring>
using namespace std;
ifstream f("integrame.in");
ofstream g("integrame.out");
char m[100][100],v[100][100];
short lung[100],n,m2,p,nra[100],i,j,k;
bool v1,v2,v3,v4;
int cautare_sus(short x,short y,short nrcuv)
{
    int lungi=lung[nrcuv],coo=0;
    while(lungi>0)
    {
        if(m[x][y]!=v[nrcuv][coo])
            return 0;
        x--;
        if(x<0)
            x=n-1;
        lungi--;
        coo++;
    }
    return 1;
}
int cautare_dreapta(short x,short y,short nrcuv)
{
    int lungi=lung[nrcuv],coo=0;
    while(lungi>0)
    {
       if(m[x][y]!=v[nrcuv][coo])
            return 0;
       y++;
       if(y>=m2)
            y=0;
       lungi--;
       coo++;
    }
    return 1;
}
int cautare_jos(short x,short y,short nrcuv)
{
    int lungi=lung[nrcuv],coo=0;
    while(lungi>0)
    {
       if(m[x][y]!=v[nrcuv][coo])
            return 0;
       x++;
       if(x>=n)
            x=0;
       lungi--;
       coo++;
    }
    return 1;
}
int cautare_stanga(short x,short y,short nrcuv)
{
    int lungi=lung[nrcuv],coo=0;
    while(lungi>0)
    {
       if(m[x][y]!=v[nrcuv][coo])
            return 0;
       y--;
       if(y<0)
            y=n-1;
       lungi--;
       coo++;
    }
    return 1;
}
int main()
{
    f>>n>>m2>>p;m[0][0]=f.get();
    for(i=0;i<n;i++)
    f.getline(m[i],100);
    for(i=0;i<p;i++)
    {
        f.getline(v[i],100);
        lung[i]=strlen(v[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m2;j++)
        {
            for(k=0;k<p;k++)
            {
                if(m[i][j]==v[k][0])
                {
                    if(cautare_sus(i,j,k)==1)
                    nra[i]++;
                    if(cautare_jos(i,j,k)==1)
                    nra[i]++;
                    if(cautare_dreapta(i,j,k)==1)
                    nra[i]++;
                    if(cautare_stanga(i,j,k)==1)
                    nra[i]++;
                }
            }
        }
    }
    for(i=0;i<p;i++)
    g<<nra[i]<<"\n";
    f.close();
    g.close();
    return 0;
}
