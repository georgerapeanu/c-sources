#include <iostream>
using namespace std;
long n,a,i,j,k,ap[100001][3],maxi;
int main()
{
    std::cin>>n;
    for(i=1;i<=n;i++)
    {
        std::cin>>a;
        if(ap[a][0]==0)
        ap[a][0]=i;
        ap[a][1]=i;
        ap[a][2]++;
    }
    for(i=1;i<=n;i++)
    {
        if(ap[i][2]>maxi)
        {
            maxi=ap[i][2];
            j=ap[i][0];
            k=ap[i][1];
        }
        else if(ap[i][2]==maxi)
        {
            if(j+k>ap[i][0]+ap[i][1])
            {
                j=ap[i][0];
                k=ap[i][1];
            }
        }
    }
    std::cout<<j<<" "<<k;
    return 0;
}
