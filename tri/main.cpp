#include <iostream>

using namespace std;
int N,nr;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        for(int j=i;j<=N;j++)
            for(int k=j;k<=N;k++)
                if(i+j+k==N&&i+j>k)
                    {nr++;cout<<i<<" "<<j<<" "<<k<<"\n";}
    cout<<"\n"<<nr;
    return 0;
}
