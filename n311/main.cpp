#include <fstream>
using namespace std;
ifstream f("n311.in");
ofstream g("n311.out");
long long int n,p=1,nr,a,b,i,v[90000000],j=1;
int main()
{
    f>>n;
    while(n!=1)
    {
        if(n%3==0)
        {
            v[j]=3;n=n/3;
            j++;
        }
        else if(n%3==1)
        {
           v[j]=1;j++;n--;
        }
        else
        {
            v[j]=-1;j++;
            n++;
        }
    }
    for(i=j-1;i>=1;i--)
    g<<v[i]<<" ";
    f.close();g.close();
    return 0;
}
