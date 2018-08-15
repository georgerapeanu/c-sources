#include <fstream>
using namespace std;
ifstream f("1.in");
ofstream g("1.out");
long i,j, ciur[100000];
int main()
{
    ciur[0]=ciur[1]=1;
    for(i=2;i<=65535;i++)
    {
        if(ciur[i]==0)
        {for(j=i+i;j<=65535;j+=i)
        ciur[j]=1;}
    }
    for(i=0;i<=65535;i++)
    if(ciur[i]==0)
        g<<i<<",";
    f.close();g.close();
    return 0;
}
