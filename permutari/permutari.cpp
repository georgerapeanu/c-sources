#include<fstream>
#include<algorithm>
using namespace std;
ifstream f("permutari.in");
ofstream g("permutari.out");
int n,k,nk,i,j,v[9];
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
        if(i==nk)
        {
        for(j=0;j<n;j++)
    {
        g<<v[j]<<" ";
    }
    g<<"\n";
         f>>nk;
        }
        next_permutation(v,v+n);
        if(i>nk)
            break;
    }
    f.close();g.close();
    return 0;
}
