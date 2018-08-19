#include <fstream>
using namespace std;
ifstream f("bila.in");
ofstream g("bila.out");
int m,n,x0[1000],y0[1000],i,j,ma[1000][1000];
void backtaking (int lin,int col, int nr)
{
    x0[nr]=lin;y0[nr]=col;
    if((lin==1&&col==1)||(lin==1&&col==m)||(lin==n&&col==m)||(lin==1&&col==m))
    {
        for(int i=1;i<=nr;i++)
        g<<x0[i]<<" "<<y0[i]<<" ";
        g<<"\n";
    }
    if(col+1<=m&&ma[lin][col+1]<ma[lin][col])//dreapta
    {
        backtaking(lin,col+1,nr+1);
    }
    if(lin+1<=n&&col<=m&&ma[lin+1][col]<ma[lin][col])  //jos
    {
        backtaking(lin+1,col,nr+1);
    }
    if(col-1>=1&&ma[lin][col-1]<ma[lin][col])//stanga
    {
        backtaking(lin,col-1,nr+1);
    }
       if(lin-1>=1&&ma[lin-1][col]<ma[lin][col]) //sus
    {
        backtaking(lin-1,col,nr+1);
    }
}
int main()
{
    int x,y;
    f>>n>>m;
    for(i=1;i<=n;i++)
     for(j=1;j<=m;j++)
    f>>ma[i][j];
    f>>x>>y;
    backtaking(x,y,1);
    f.close();g.close();
    return 0;
}
