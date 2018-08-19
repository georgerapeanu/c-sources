#include <fstream>
using namespace std;
ifstream f("zid.in");
ofstream g("zid.out");
int n;
bool gasit;
int S[1010],i,V[1010],st=1,dr,j;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>V[i];
        S[i]=(S[i-1]+V[i])%n;
        if(S[i]==0){gasit=1;dr=i;st=1;}
    }
    if(gasit)
    {
        g<<dr-st+1<<"\n";
        for(i=st;i<=dr;i++)
            g<<V[i]<<" ";
    }
    else
    {
        for(i=1;i<=n&&!gasit;i++)
        {
            for(j=i;j<=n&&!gasit;j++)
                if(S[j]-S[i-1]==0)
                {
                    st=i;
                    dr=j;
                    gasit=1;
                }
        }
        g<<dr-st+1<<"\n";
        for(i=st;i<=dr;i++)
            g<<V[i]<<" ";
    }
    return 0;
}
