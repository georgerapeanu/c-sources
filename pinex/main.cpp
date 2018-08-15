#include <iostream>
#include <vector>
#include <bitset>
#include <cstdio>
#define VMAX 1000005
#define pb push_back
using namespace std;
long long A,B;
bitset<VMAX> E;
vector<int> P;
long long q(long long val)
{
    vector<long long> div;
    for(auto it:P)
    {
        if(it>val) break;
        if(val%it!=0) continue;
        div.pb(it);
        while(val%it==0)
            val/=it;
    }
    if(val>1)
        div.pb(val);
    int N=div.size();
    long long sol=0;
    for(int i=0;i<(1<<N);i++)
    {
        long long rez=1,op=1;
        for(int j=0;j<N;j++)
            if((1<<j)&i)
            {rez*=div[j];op*=-1;}
        sol+=(A/rez)*op;
    }
    return sol;
}
int main()
{
    freopen("pinex.in","r",stdin);
    freopen("pinex.out","w",stdout);
    E[0]=E[1]=1;
    for(int i=2;i*i<VMAX;i++)
    {
        if(!E[i])
        {
            for(int j=i*i;j<VMAX;j+=i)
                E[j]=1;
        }
    }
    for(int i=2;i<VMAX;i++) if(!E[i]) P.pb(i);
    int T;
    cin>>T;
    while(T)
    {
        cin>>A>>B;
        cout<<q(B)<<"\n";
        T--;
    }
    return 0;
}
