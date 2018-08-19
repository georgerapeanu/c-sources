#include <fstream>
#include <iostream>
using namespace std;
ifstream f("numere6.in");
ofstream g("numere6.out");
int a,b,uc,pc,nrc,ca,c,d,n10=1,a2,b2,a3=1,b3=1;
int main()
{
    cin>>a>>b;
    ca=a;
    while(a!=0)
    {
        a2+=((a%10)%2)*a3;a3=a3*10;
        a=a/10;
        n10=n10*10;
    }
    n10/=10;
    while(b>9)
    {
        b2+=((b%10)%2)*b3;b3=b3*10;
        b=b/10;
        n10=n10*10;
    }
    cout<<a2<<" "<<b2;
    return 0;
}
