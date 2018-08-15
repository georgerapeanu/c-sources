#include <fstream>
using namespace std;
ifstream f("rubine.in");
ofstream g("rubine.out");
long v[2000000],ciur[2000000],i,n,k,p,j,a,b1,b2,c,sf1,sf2;
int main()
{
    f>>n>>k>>p;ciur[0]=ciur[1]=1;
    for(i=2;i<=n;i++)
    {
        if(ciur[i]==0)
        {
            for(j=i+i;j<=n;j++)
            ciur[j]=1;
        }
    }
    for(i=1;i<=n;i++)
    {
        f>>v[i];
        if(ciur[v[i]]==0)
        a++;
    }
    i=1;j=1;sf1=1;sf2=1;
    while(sf1!=0||sf2!=0)
    {
        i=i+k;j=j+p;
        if(i>n)
        i=i-n;
        if(j>n)
        j=j-n;
        if(ciur[j]==1&&sf2!=0)
        {
            if(ciur[i]==1&&sf1!=0)
            {
                if(v[i]==-3)
                {
                    sf1=sf2=0;break;
                }
                else if(v[i]=-2)
                {
                    sf2=0;break;
                }
                else if(v[i]==-1)
                {
                    sf1=0;break;
                }
                else
                {
                    if(i==j)
                     {if(n%2==1)
                    b1+=n/2+1;
                    else
                    b1+=n/2;
                    b2+=n/2;
                    v[i]=-3;}
                    else
                    {
                        b1+=v[i];
                        b2+=v[j];
                        v[j]=-1;
                        v[i]=-1;
                    }
                }
            }
            else
            {
                   if(v[i]==-2)
                {
                    sf2=0;break;
                }
                else
                {
                     b2+=v[j];
                     v[j]=-2;
                }
            }
        }
        else
        {
            if(v[i]==-1)
            {sf1=0;break;}
            else
            {
                b2+=v[i];
                v[i]=-1;
            }
        }
    }
    g<<a<<"\n"<<b1<<" "<<b2<<"\n"<<c;
    f.close();g.close();
    return 0;
}
