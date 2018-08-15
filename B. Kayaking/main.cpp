#include <iostream>
#include <algorithm>
using namespace std;
int N;
int V[105];
int main()
{
    cin>>N;for(int i=1;i<=2*N;i++)cin>>V[i];
    sort(V+1,V+1+2*N);
    int rez=1<<30;
    for(int i=1;i<=2*N;i++)
    {
        for(int j=i+1;j<=2*N;j++)
        {
            int tmp=0,last=0;
            for(int k=1;k<=2*N;k++)
            {
                if(k!=i&&k!=j)
                {
                    if(last==0)last=k;
                    else
                    {
                        tmp+=V[k]-V[last];
                        last=0;
                    }
                }
            }
            rez=min(tmp,rez);
        }
    }
    cout<<rez;
    return 0;
}
