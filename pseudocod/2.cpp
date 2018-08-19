#include<iostream>
using namespace std;
int main()
{
    int x,y,n,s;
    cout<<"x=";
    cin>>x;
    cout<<"y=";
    cin>>y;
    cout<<"n=";
    cin>>n;
    s=0;
    if(x%2==0)
    {
        if(y%2==0)
        {
            s=(y-x)*(x+y)/4;
        }
        else
            s=(y-x+1)*(x+y+1)/4;
    }
    else
    {
         if(y%2==0)
        {
            s=(y-x+1)*(x+y-1)/4;
        }
        else
            s=(y-x+2)*(x+y)/4;
    }
    if(s==n)
        cout<<"1";
    else
        cout<<"0";
}
