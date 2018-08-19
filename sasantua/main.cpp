#include <iostream>
using namespace std;
long long int n,i,c=1,j,p,cmax=1;
char g=92;
int sasantua(int l)
{
    for(p=1;p<cmax-(c/2)-2;p++)
        cout<<" ";
    cout<<"/";
    for(p=1;p<=c;p++)
        cout<<"*";
    cout<<g<<"\n";
}
int putchar(int l)
{
   for(p=1;p<cmax-(c/2)-2;p++)
        cout<<" ";
    cout<<"/";
    for(p=1;p<=c/2-n/2;p++)
        cout<<"*";
    for(p=1;p<=n;p++)
        cout<<"|";
    for(p=c/2+n/2;p<=c;p++)
        cout<<"*";
    cout<<g<<"\n";
}
int main()
{
    cin>>n;cout<<"\n";

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i+2;j++)
        {
        cmax+=2;
        }
        cmax+=4;
    }
    cmax=cmax/2;
     for(i=1;i<=n;i++)
    {
        for(j=1;j<=i+2;j++)
        {
        sasantua(i);
        c+=2;
        }
        c+=4;
    }
    return 0;
}
