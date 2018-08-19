#include <iostream>
using namespace std;
char c;
int a,b,N,i;
bool ok;
int main()
{
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>a>>c>>b;
        ok=0;
        if(a>=0&&a<24&&b>=0&&b<60)
        {
            if(b==0)
                ok=1;
            else if(a==b)
                ok=1;
            else if(a==b/10+(b%10)*10)
                ok=1;
            else if(b==a+22)
                ok=1;
            else if((a==10&&b==24)||(a==20&&b==48))
                ok=1;
        }
        if(ok==1)
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}
