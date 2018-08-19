#include <iostream>

using namespace std;
int a,b;
int N;
int st,dr;
long long A,B;
int main()
{
    cin>>a>>b>>N;
    st=1;
    dr=N;
    A=1LL*st*a+b;
    if(N==2) B=1LL*2*a+b;
    else
    {
        long long nr=3,poz=1;
        while(nr-(1LL<<poz)+(1LL<<(poz+1))<=N)
        {
            nr=nr-(1LL<<poz)+(1LL<<(poz+1));
            poz++;
        }
        B=1LL*nr*a+b;
    }
    cout<<A<<" "<<B;
    return 0;
}
