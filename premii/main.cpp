#include <fstream>
using namespace std;
ifstream f("premii.in");
ofstream g("premii.out");
short ob[11];
short val[11],i,n;
int corectitudine()
{
    long long suma1=0,suma2=0;
    for(i=1;i<=n;i++)
    if(ob[i]==0)
    suma1+=val[i];
    else if(ob[i]==1)
    suma2+=val[i];
    if(suma1==suma2)
    return 1;
    else
    return 0;
}
void back(int l)
{
    if(l<=n)
    {
        ob[l]=0;
        back(l+1);
        ob[l]=1;
        back(l+1);
        ob[l]=2;
        back(l+1);
    }
    else if(corectitudine()==1)
    {
        val[0]++;
    }
}
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    f>>val[i];
    back(1);
    g<<(val[0]-1);
    f.close();g.close();
    return 0;
}
