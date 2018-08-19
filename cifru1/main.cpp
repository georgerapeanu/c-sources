#include <fstream>
using namespace std;
ifstream f("cifru1.in");
ofstream g("cifru1.out");
long s;
int i,j,m[101][101],l1,l2,l3,l4,a=1,b=0,k,v[51],n,nr,aux;
int rotire( int nr1)
{
             for(i=k;i<=n-k;i++)
           {
               aux=m[k][i];
               m[k][i]=m[i][n+1-k];
               m[i][n+1-k]=m[n+1-k][n+1-i];
               m[n+1-k][n+1-i]=m[n+1-i][k];
               m[n+1-i][k]=aux;
           }
           if(nr1>1)
           rotire(nr1-1);
}
int main()
{
    //l1 pentru N
    //l2 pentru V
    //l3 pentru S
    //l4 pentru E
    f>>n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        f>>m[i][j];
    }
    for(k=1;k<=n/2;k++)
    {
       l1=l2=l3=l4=0;
       for(i=k;i<=n-k+1;i++)
       {
           l1+=m[k][i];
           l2+=m[i][k];
           l3+=m[n-k+1][i];
           l4+=m[i][n-k+1];
       }
       nr=(l1>l2 ? l1:l2);
       nr=(nr>l3 ? nr:l3);
       nr=(nr>l4 ? nr:l4);
       s+=nr;
       if(nr==l1)
       {
           continue;
       }
       else if(nr==l2)
       {
           rotire(3);
       }
       else if(nr==l3)
        {
            rotire(2);
        }
       else
       {
            rotire(1);
       }
    }
    g<<s<<"\n";
       for(i=1;i<=n;i++)
    {
    for(j=1;j<=n;j++)
    {
        g<<m[i][j]<<" ";
    }
    g<<"\n";
    }
    f.close();g.close();
    return 0;
}
