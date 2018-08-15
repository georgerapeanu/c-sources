#include<iostream>
using namespace std;
int main()
{

    int a,b,j,x,y,k;
    float jj;
    cout<<"a=";
    cin>>a;
    cout<<"b=";
    cin>>b;
    j=0;
    for(y=a;y<=b;y++)
    {
     k=0;
    for(x=2;x<=y/2;x++)
    {
        if(y%x==0)
        {
        x=y/2+1;k=1;
        }
    }
    if(k==0)
        {
            j=y;
            y=b+1;
        }
    }
    jj=j/4;
    cout<<j<<" "<<jj;
    if(j==0)
        cout<<"imposibil";
    else if(j+jj>b)
    cout<<"imposibil";
    else
        cout<<j<<" "<<jj;
return 0;
}
