#include <iostream>
using namespace std;
int N;
int a;
int xo;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        for(int j=2;1LL*j*j<=a;j++)
        {
            if(a%j==0)
            {
                int e=0;
                while(a%j==0)
                {
                    e++;
                    a/=j;
                }
                xo^=e;
            }
        }
    }
    cout<<(xo==0 ? "Arpa":"Mojtaba");
    return 0;
}
