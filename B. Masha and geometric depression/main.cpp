#include <iostream>
#include <cmath>
#include <map>
using namespace std;
int b,q,l,m;
int a;
bool ok,tmp;
map<int,int> B;
map<int,int> viz;
int main()
{
    cin>>b>>q>>l>>m;
    for(int i=1;i<=m;i++)
        {cin>>a;B[a]=1;}
    if(q==0)
    {
        if(abs(b)>l) cout<<0;
        else if(B[b]==1&&B[0]==1) cout<<0;
        else if(B[0]==1) cout<<1;
        else cout<<"inf";
    }
    else if(abs(q)==1)
    {
        if(B[b]==1&&B[b*q]==1)
            cout<<"0";
        else if(abs(b)>l)
            cout<<"0";
        else cout<<"inf";
    }
    else
    {
        if(b==0)
        {
            if(B[b]==1)
                cout<<0;
            else
                cout<<"inf";
            return 0;
        }
        int nr=0;
        while(abs(b)<=l)
        {
            if(B[b]==0)
                nr++;
            if(abs(b)>abs(l/q))
                break;
            b=b*q;
        }
        cout<<nr;
    }
    return 0;
}
