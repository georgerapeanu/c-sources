#include<fstream>
using namespace std;
ifstream f("baschet.in");
ofstream g("baschet.out");
int main()
{
    int n,i,k=1,maxim=0,l=0,p=0,u=0,s=0,d=0,j=0;
    f>>n;
    int v[n];
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    for(i=0;i<n;i++)
    {
        if(v[i]==v[i+1])
        {
            k++;
            maxim=k;
        }
        else
            k=0;
        if(maxim==k&&k!=0)
        {
            if(p==0)
            {
            l=i;
            p=1;
            }
            else
                u=i+1;
        }
        if(maxim!=k)
            i=n;
    }
    d=u-l+1;
    for(j=l;j<=u;j++)
    {
        s=s+v[j];
    }
    g<<d<<" "<<s;
    f.close();g.close();
    return 0;
}
