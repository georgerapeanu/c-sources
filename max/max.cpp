#include<fstream>
#include<iostream>
#include<algorithm>
using namespace std;
ifstream f("max.in");
ofstream g("max.out");
int main()
{
    int n,i,c,d=0,y,maxim=0,a,uc,b,j,e;
    f>>n;
    int v[n],p[3501];
    for(i=1;i<=n;i++)
    {
        f>>y;v[i]=y;
        if(v[i]<10)p[i]=10;
         if(y>=10&&y<100)
        {
            a=y/10;p[i]=100;
            b=y%10;
            if(a<b)
                v[i]=b*10+a;
        }
        if(y>=100)
        {
            a=y/100;b=y/10%10;c=y%10;p[i]=1000;
            if(a<c){y=a;a=c;c=y;}
            if(a<b){y=a;a=b;b=y;}
            if(b<c){y=b;b=c;c=y;}
            v[i]=a*100+b*10+c;
        }
        if(maxim<v[i])
            maxim=v[i];
    }
    g<<maxim<<"\n";
for(i=0;i<n;i++)
{
    for(j=i+1;j<=n;j++)
    {
        d=v[i];d=d*p[j]+v[j];e=v[j];e=e*p[i]+v[i];
        if(d<e){y=v[i];v[i]=v[j];v[j]=y;
                y=p[i];p[i]=p[j];p[j]=y;}
    }
}
for(i=1;i<=n;i++) g<<v[i];
g.close();
    return 0;
}
