#include <fstream>
using namespace std;
using namespace std;
ifstream f("cifre3.in");
ofstream g("cifre3.out");
long long a,b,uca,ucb,gasit,cfa[10],cfb[10],i;
int main()
{
    f>>a>>b;
    while(a!=0)
    {
        uca=a%10;
        a=a/10;
        cfa[uca]++;
    }
    while(b!=0)
    {
        ucb=b%10;
        b=b/10;
        cfb[ucb]++;
    }
    for(i=0;i<=9;i++)
    {
        if(cfa[i]!=0&&cfb[i]!=0)
            g<<i<<" ";
        cfa[i]+=cfb[i];
    }
    g<<"\n";
    for(i=9;i>=0;i--)
    {
        while(cfa[i]!=0)
        {
            g<<i;
            cfa[i]--;
        }
    }
    f.close();g.close();
    return 0;
}
