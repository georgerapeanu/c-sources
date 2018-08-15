#include<fstream>
using namespace std;
ifstream f("matrixdel.in");
ofstream g("matrixdel.out");
int main()
{
    int l,c,q,p,i,j,k,gasit=0;
    f>>l>>c;
    int a[l][c],v[l][c];
    for(i=0;i<l;i++)
    {
        for(j=0;j<c;j++)
        {
            f>>a[i][j];
            v[i][j]=1;
        }
    }
    f>>p;
    int s[p];
    for(i=0;i<p;i++)
    {
        f>>s[i];
    }
    f>>q;
    int d[q];
    for(i=0;i<q;i++)
    {
        f>>d[i];
    }
    for(j=0;j<p;j++)
    {
    for(i=0;i<l;i++)
    {
      for(k=0;k<c;k++)
      {
          if(i+1==s[j])
          {
              v[i][k]=0;
          }
      }
    }
    }
    for(j=0;j<q;j++)
    {
    for(i=0;i<l;i++)
    {
      for(k=0;k<c;k++)
      {
          if(k+1==d[j])
          {
              v[i][k]=0;
          }
      }
    }
    }
    for(i=0;i<l;i++)
    {
        if(gasit==1)
            g<<"\n";
        gasit=0;
        for(j=0;j<c;j++)
        {
            if(v[i][j]==1)
            {g<<a[i][j]<<" ";gasit=1;}
        }
    }
    f.close();g.close();
    return 0;
}
