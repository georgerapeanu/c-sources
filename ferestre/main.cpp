#include <fstream>
#include <iostream>
using namespace std;
ifstream f("ferestre.in");
ofstream g("ferestre.out");
int m[201][5],i,out[201],nr,n,ma,j,k;
bool matrix[201][201];
bool gasit,gasit2=0;
int main()
{
    f>>n>>ma;
    for(i=1;i<=n;i++)
    f>>m[i][1]>>m[i][2]>>m[i][3]>>m[i][4];
    for(i=1;i<=ma;i++)
    {f>>nr;m[nr][0]=1;}
    for(i=n;i>=1;i--)
    {
      if(m[i][0]==1)
      {
          gasit=1;
          for(j=m[i][1];j<=m[j][3];j++)
          for(k=m[i][2];k<=m[i][4];k++)
          {
              matrix[j][k]=1;
          }
      }
      else if(gasit==0)
      {
          out[++out[0]]=i;
      }
      else
      {
           if(matrix[m[i][1]][m[i][4]]==1)
           out[++out[0]]=i;
      }
    }
    for(i=0;i<=out[0];i++)
    g<<out[i]<<"\n";
    return 0;
}
