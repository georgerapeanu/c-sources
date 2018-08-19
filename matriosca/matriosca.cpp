#include<fstream>
using namespace std;
ifstream f("papusa.in");
ofstream g("papusa.out");
int main()
{
    int p,n,j,l,maxim=1,maxi=1,m1=1,i,m2=1,hold,q;
    f>>n;
    int v[n],m[n/2];
    for(j=0;j<n;j++)
    {
        f>>v[j];
    }
    for(j=0;j<n/2;j++)
    {
        m1=1;
        m2=1;
    for(i=0;i<n/2-1;i++)
    {
        if(v[i]>v[i+1])
        {
            m1++;
        }
        else
            i=n/2;
    }
    for(i=n-1;i>n/2;i--)
    {
        if(v[i]>v[i-1])
        {
            m2++;
        }
        else
            i=n/2;
   }
   p=m1+m2;
   if(maxim<p)
    maxim=p;
    m1=1;
    m2=1;
    for( i=n/2-1;i>0;i--)
    {
        if(v[i]>v[i-1])
        {
            m1++;
        }
        else
            i=0;
    }
    for(i=n/2;i<n-1;i++)
    {
        if(v[i]>v[i+1])
        {
            m2++;
        }
        else
            i=n;
}
p=m1+m2;
if(maxim<p)
    maxim=p;
 m[j]=maxim;
 hold=v[0];
 for(i=0;i<n/2-1;i++)
 {
     v[i]=v[i+1];
 }
 v[n/2-1]=hold;
 hold=v[n/2];
 for(i=n/2;i<n-1;i++)
 {
     v[i]=v[i+1];
 }
 v[n-1]=hold;
}
maxi=1;
for(j=0;j<n/2;j++)
{
    if(maxi<m[j])
    {
        maxi=m[j];q=j;
    }
}
g<<q<<"\n"<<maxi;
    return 0;
}
