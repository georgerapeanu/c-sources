#include<fstream>
#include<algorithm>
using namespace std;
ifstream f("permfix.in");
ofstream g("permfix.out");
long n,k,nk,j,l,v[9],i;
int main()
{
   f>>n>>k>>nk;
    k=1;
    for(i=0;i<n;i++)
    {
        v[i]=i+1;
        k=k*(i+1);
    }
    for(i=1;i<=k;i++)
    {
        for(l=0;l<n;l++)
        {
            if(v[l]==(l+1))
            {
                break;
            }
        }
        if(l==n)
        {
            j++;
            if(nk==j)
            {
            for(l=0;l<n;l++)
                g<<v[l]<<" ";
            g<<"\n";
            f>>nk;
            }
        }
        if(j==k)
            break;
        next_permutation(v,v+n);
    }
}
