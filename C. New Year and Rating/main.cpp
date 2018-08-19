#include<iostream>
#include<fstream>
#include<string>
#define MAXIM 200000000
using namespace std;
string s;
int N;
int i,j,c,d,poz=0,dr=-MAXIM,st=MAXIM;
int main()
{
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>c>>d;
        if(d==1)
            st=min(st,poz);
        else
            dr=max(dr,poz);
        poz=poz+c;
    }
    if(st<=dr)
    {
        cout<<"Impossible\n";
        return 0;
    }
    if(dr==-MAXIM)
    {
        cout<<"Infinity\n";
    }
    else
    {
        c=poz-dr;
        cout<<1899+c<<"\n";
    }
    return 0;
}
