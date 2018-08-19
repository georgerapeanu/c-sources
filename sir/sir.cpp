#include<iostream>
#include<fstream>
using namespace std;
ifstream f("sir.in");
ofstream g("sir.out");
int main()
{
    int y,d,a,b,k,i,j,l,s=0,u,c=0;
    long x,r=1;
    f>>k;
    f>>x;
    f>>a;
    f>>b;
    l=k;
    u=x;
    for(i=1;i<=k;i++)
{
    s=s+i*l;
    l--;
}
while(u!=0)
{
    u=u/10;
    r=r*10;
}
r=r/10;
s=s%10;
g<<s<<endl;
d=x/r;
d=d+(x%r)*10;
g<<d<<endl;
y=0;
while(y<(b-a))
    y++;
g<<y;
f.close();g.close();
return 0;
}
