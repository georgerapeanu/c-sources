#include <iostream>
#include <algorithm>
using namespace std;
int a,b,minim,maxim,T,Q,rez,rez2,d;
int main()
{
    cin>>Q;
    while(Q)
    {
        cin>>a>>b>>d;
        if(d==0)
            cout<<"0\n";
        else if(d==a)
            cout<<"1\n";
        else if(d>=b)///cu o lat de x,putem atinge toate dist x<=dist<=2x in 2 pasi.apoi,luan combinatia de laturi 2x si x,putem sa le marcam pe cele pana la 3x in 3 pasi.etc(inegalitatea triunghiului)
            cout<<(d+b-1)/b<<"\n";///cele 1<=dist<x in 2 pasi
        else
            cout<<2<<"\n";
        Q--;
    }
    return 0;
}
