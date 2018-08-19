#include <iostream>

using namespace std;
long long a,b,c,d;
long long rez;
long long mini(long long a,long long b,long long c)
{
    return min(a,min(b,c));
}
int main() {
    cin>>a>>b>>c>>d;
    int tmp=min(a,mini(b,c,d));
    int val=max(max(a,b),max(c,d));
    if(a==tmp)
    {
        tmp=mini(b,c,d);
        int scad=(tmp-a)/3+((tmp-a)%3!=0);
        rez=max(rez,max(val+a*2,val-scad+2*min(a+2*scad,mini(b-scad,c-scad,d-scad))));
    }
    else if(b==tmp)
    {
        tmp=mini(a,c,d);
        int scad=(tmp-b)/3+((tmp-b)%3!=0);
        rez=max(rez,max(val+b*2,val-scad+2*min(b+2*scad,mini(a-scad,c-scad,d-scad))));
    }
    else if(c==tmp)
    {
        tmp=mini(b,a,d);
        int scad=(tmp-c)/3+((tmp-c)%3!=0);
        rez=max(rez,max(val+c*2,val-scad+2*min(c+2*scad,mini(b-scad,a-scad,d-scad))));
    }
    else
    {
        tmp=mini(b,c,a);
        int scad=(tmp-d)/3+((tmp-d)%3!=0);
        rez=max(rez,max(val+d*2,val-scad+2*min(d+2*scad,mini(b-scad,c-scad,a-scad))));
    }
    cout<<rez;
    return 0;
}
