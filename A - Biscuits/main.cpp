#include <iostream>
using namespace std;
int nrp,nri;
int P;
int N;
long long rez;
long long C[55][55];
int main()
{
    cin>>N>>P;
    for(int i=1;i<=N;i++)
    {
        int val;cin>>val;
        if(val%2==0)nrp++;
        else        nri++;
    }
    for(int i=0;i<=nri;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    for(int k=0;2*k+P<=nri;k++)
        rez=rez+(1LL<<nrp)*C[nri][2*k+P];
    cout<<rez;
    return 0;
}
