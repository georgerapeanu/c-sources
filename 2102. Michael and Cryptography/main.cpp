#include <iostream>
#include <vector>
#define MAX 1000000
#define LL long long
using namespace std;
LL N;
LL c,nr;
bool E[MAX+1];
vector<LL> P;
int main()
{
    cin>>N;
    E[0]=E[1]=1;
    for(LL i=2;i*i<=MAX;i++)
    {
        if(!E[i])
        {
            for(LL j=i*i;j<=MAX;j+=i)
            {
                E[j]=1;
            }
        }
    }
    for(LL i=2;i<=MAX;i++)
    {
        if(!E[i])
            P.push_back(i);
    }
    for(int i=0;i<P.size()&&P[i]<=N;i++)
    {
        while(N%P[i]==0)
        {
            c++;
            N/=P[i];
        }
    }
    if(c>=18&&N!=1)
    {
        for(LL i=MAX;i*i<=N;i++)
        {
            if(N%i==0)
            {
                c++;
                break;
            }
        }
        c++;
    }
    if(c==20)
        cout<<"Yes";
    else
        cout<<"No";
    return 0;
}
