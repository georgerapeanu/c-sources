#include<fstream>
using namespace std;
ifstream f("joc.in");
ofstream g("joc.out");
int n,i,s,a,gasit=0;
int main()
{
f>>n;
for(i=1;i<=n;i++)
{
    f>>a;
    if(i==1)
       s=a/100%10;
    else
    {
        if(a/1000!=s)
        {
            g<<i<<" ";
            gasit=1;
        }
        s=a/100%10;
    }
}
if(gasit==0)
g<<"0";
f.close();g.close();
return 0;
}
