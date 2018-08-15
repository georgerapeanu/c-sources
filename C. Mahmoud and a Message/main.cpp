#include <iostream>
#include <cstring>
#include <unordered_map>
#define MOD 1000000007
using namespace std;
int N;
char C[1005];
int a[1005];
int b[1005];
int c[1005];
unordered_map<int,int> M;
unordered_map<int,int> tmp;
int main()
{
    cin>>N;cin.getline(C+1,1005);
    cin.getline(C+1,1005);
    for(int i=0;i<26;i++)
    {
        int val;
        cin>>val;
        M['a'+i]=val;
    }
    a[0]=1;
    int j;
    for(int i=1;i<=N;i++)
    {
        j=i;
        int dim=1005;
        c[i]=1005;
        while(j>0)
        {
            dim=min(dim,M[C[j]]);
            if(i-j+1>dim) break;
            a[i]=(a[i]+a[j-1])%MOD;
            b[i]=max(b[i],max(b[j-1],i-j+1));
            c[i]=min(c[i],c[j-1]+1);
            j--;
        }
    }
    cout<<a[N]<<"\n"<<b[N]<<"\n"<<c[N];
    return 0;
}
