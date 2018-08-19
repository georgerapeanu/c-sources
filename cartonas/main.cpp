#include <fstream>
using namespace std;
ifstream f("cartonas.in");
ofstream g("cartonas.out");
long long int c[100][100],v[100],s,i,n,x,ga,j,u=1,minim=9999999,tm;
int main()
{
    f>>n>>x;
    for(i=0;i<n;i++)
    {
        f>>c[0][i];
        if(x==c[0][i])
            ga=1;
            s+=c[0][i];
    }
    while(s!=0)
    {
       v[0]=s%2*u+v[0];
       u=u*10;
       s=s/2;
       if(s==1)
            break;
    }
    v[0]=v[0]+u;
    for(i=1;i<n;i++)
    {
        s=0;u=1;
        for(j=0;j<=n-i;j++)
        {
            c[i][j]=c[i-1][j]+c[i-1][j+1];s+=c[i][j];
            if(x==c[i][j]&&ga==0)
                ga=i+1;
        }
         while(s!=0)
    {
       v[i]=s%2*u+v[i];
       u=u*10;
       s=s/2;
       if(s==1)
            break;
    }
    v[i]=v[i]+u;
    }
    g<<c[n-1][0]<<"\n"<<ga<<" ";
    for(i=0;i<n;i++)
    {
        minim=9999999;
        for(j=0;j<n;j++)
        {
            if(minim>v[j])
            {minim=v[j];tm=j;}
        }
        g<<(tm+1)<<" ";
        v[tm]=9999999;
    }
    f.close();g.close();
    return 0;
}
