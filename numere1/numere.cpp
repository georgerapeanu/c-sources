#include<fstream>
using namespace std;
ifstream f("numere.in");
ofstream g("numere.out");
int ciur[101];
int main()
{
    int p,a,b,i,j;
    f>>p>>a>>b;
    if(p==1)
    {
        int nrd=0;
        for(i=1;i<=a;i++)
        {
            if(a%i==0)
                nrd++;
        }
        g<<nrd;
    }
    else
    {
        ciur[1]=1;
        for(i=2;i<=b;i++)
        {
            if(ciur[i]==0)
            {
                for(j=i+i;j<=b;j+=i)
                {
                    ciur[j]=1;
                }
            }
        }
        for(i=2;i<=b;i++)
            {
                if(ciur[i]==0)
                    g<<i<<"\n";
            }
    }
    f.close();g.close();
    return 0;
}
