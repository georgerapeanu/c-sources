#include <iostream>
using namespace std;
int V[2005];
bool E[100005];
int N,g,rez;
int nrone;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
bool ok()
{
    for(int i=1;i<=N;i++)
        if(V[i]!=1)return 0;
    return 1;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {cin>>V[i];g=gcd(g,V[i]);nrone+=(V[i]==1);}
    if(g!=1){cout<<-1;return 0;}
    if(!nrone)
    {
        int x=0,y=N+1;
        for(int i=1;i<=N;i++)
        {
            int g=0;
            for(int j=i;j<=N;j++)
            {
                g=gcd(g,V[j]);
                if(g==1)
                {
                    if(y-x+1>j-i+1)
                    {
                        x=i;
                        y=j;
                    }
                    break;
                }
            }
        }
        rez=(y-x+N-1);
    }
    else
    {
        rez=N-nrone;
    }
    cout<<rez;
    return 0;
}
