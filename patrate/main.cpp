#include <fstream>
#include <math.h>
#include <iostream>
using namespace std;
ifstream f("patrate.in");
ofstream g("patrate.out");
long long m[100][100],n,l[100][100];
void s1()
{
    long long temp=0,i,j;
   for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			m[i][j]=(i-1)*n+j;
   for(i=1;i<=n/2;i++)
   {
       if(i%4==0||i%4==1)
       {
           j=-1;
        while(j<=n)
        {
            j+=3;
            temp=m[i][j];
            m[i][j]=m[n-i+1][n-j+1];
            m[n-i+1][n-j+1]=temp;
            j++;
            temp=m[i][j];
            m[i][j]=m[n-i+1][n-j+1];
            m[n-i+1][n-j+1]=temp;
        }
       }
       else
       {
             j=0;
        while(j<=n)
        {
            j++;
            temp=m[i][j];
            m[i][j]=m[n-i+1][n-j+1];
            m[n-i+1][n-j+1]=temp;
            j+=3;
            temp=m[i][j];
            m[i][j]=m[n-i+1][n-j+1];
            m[n-i+1][n-j+1]=temp;
        }
       }
   }

}
void s3()
{
	int max=1,lin=1,col=ceil(double(n)/2);
	m[lin][col]=1;
	max++;
  while(max<=n*n)
  {
    if(lin==1)
    {
       if(col>=2&&m[n][col-1]==0)
       {
           col--;
           lin=n;
       }
       else if(col==1&&m[n][col]==0)
       lin=n;
       else
       lin++;
    }
    else if(col==1)
    {
       if(lin>=2&&m[lin-1][n]==0)
       {
           lin--;
           col=n;
       }
       else if(lin==1&&m[lin][n]==0)
       col=n;
       else
       lin++;
    }
    else
    {
         if(m[lin-1][col-1]==0)
          {lin--;col--;}
        else
          lin++;
    }
    m[lin][col]=max;
    max++;
  }
}
void s2()
{
    n/=2;
      s3();
      n*=2;
      for(int i=1;i<=n;i+=2)
      {
          for(int j=1;j<=n;j+=2)
          {
              if(i/2+1<=n/4+1)
              {
                    l[i][j+1]=(m[i/2+1][j/2+1]-1)*4+1;
                    l[i+1][j]=(m[i/2+1][j/2+1]-1)*4+2;
                    l[i+1][j+1]=(m[i/2+1][j/2+1]-1)*4+3;
                    l[i][j]=(m[i/2+1][j/2+1]-1)*4+4;
              }
              else if(i/2==n/4+2)
              {
                  l[i][j]=(m[i/2+1][j/2+1]-1)*4+1;
                  l[i+1][j]=(m[i/2+1][j/2+1]-1)*4+2;
                  l[i+1][j+1]=(m[i/2+1][j/2+1]-1)*4+3;
                  l[i][j+1]=(m[i/2+1][j/2+1]-1)*4+4;
              }
              else
              {
                  l[i][j]=(m[i/2+1][j/2+1]-1)*4+1;
                  l[i+1][j+1]=(m[i/2+1][j/2+1]-1)*4+2;
                  l[i+1][j]=(m[i/2+1][j/2+1]-1)*4+3;
                  l[i][j+1]=(m[i/2+1][j/2+1]-1)*4+4;
              }
          }
      }
}
int main()
{
	f>>n;
	if(n%4==0)
		s1();
	else if(n%4==2)
		s2();
	else
		s3();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			g<<l[i][j]<<" ";
		g<<"\n";
	}
	f.close();g.close();
	return 0;
}
