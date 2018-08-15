#include <fstream>
using namespace std;
ifstream f("nenepatrat.in");
ofstream g("nenepatrat.out");
long nrdiv,n,prim[300000000],l;
bool ciur[2000000001];
void f_ciur()
{
    long i,j;
    ciur[0]=ciur[1]=true;
    for(i=2;i<=n;i++)
    {
        if(ciur[i]==false)
        {
            prim[++l]=i;
            for(j=i*i;j<=n;j+=i)
            ciur[j]=true;
        }
    }
}
void div
int main()
{
    f>>n;
    f_ciur();
    div(n,1);
    return 0;
}
