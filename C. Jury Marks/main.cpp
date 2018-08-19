#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#define LIM 8000005
using namespace std;
int N,K;
int A[2005];
int S[2005];
int B[2005];
int rez;
int lst[2*LIM+1];
int nr[2*LIM+1];
int main()
{
    int lasamainpace=1;
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>K>>N;
    for(int i=1;i<=K;i++){cin>>A[i];S[i]=A[i]+S[i-1];}
    for(int i=1;i<=N;i++)cin>>B[i];
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=K;j++)
        {
            int x=S[j]-B[i];
            if(lst[LIM+x]!=i)
            {
                nr[LIM+x]++;
                lst[LIM+x]=i;
            }
        }
    }
    for(int i=0;i<=2*LIM;i++)
        rez+=(nr[i]>=N);
    cout<<rez;
    return 0;
}
