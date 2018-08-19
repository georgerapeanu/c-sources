#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;
ifstream f("apropiate1.in");
ofstream g("apropiate1.out");
bool ciur[4000000];
long long x,y,n,a,i,j;
int c;
int main()
{
    f>>n>>c;cout<<sizeof(long long);
    ciur[1]=ciur[0]=true;
    for(i=2;i<=4000000;i++)
    {
        if(ciur[i]==false)
        for(j=i*i;j<=4000000;j+=i)
        {
            ciur[j]=true;
        }
    }
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(ciur[a]==false)
        g<<a<<" ";
        else
        {
            x=y=a;
            while(ciur[x]==true&&ciur[y]==true&&x>0&&y<4000000)
            {
                x--;y++;
            }
            if(ciur[x]==false&&ciur[y]==false)
            {
                if(c==1)
                  g<<x<<" ";
                else
                g<<y<<" ";
            }
            if(ciur[x]==true&&ciur[y]==false)
            g<<y<<" ";
            if(ciur[x]==false&&ciur[y]==true)
            g<<x<<" ";
        }
    }
    f.close();g.close();
    return 0;
}
