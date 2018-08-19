#include <iostream>
#include <cmath>
using namespace std;
int T;
long long rez;
long double nr;
long double tmp;
long double minim;
int main() {
    cin>>T;
    while(T--)
    {
        cin>>nr;
        nr/=(1e9);
        minim=(1e9);
        for(int x=0;(long double)x*x+nr<=(1e9);x++)
        {
            tmp=(x+nr)*(x+nr);
            long long a=tmp;
            cout<<minim<<"\n";
            if(tmp-a<minim&&a>0){minim=tmp-a;rez=a;}
            if(a+1-tmp<minim&&a+1<=1000000000){minim=a+1-tmp;rez=(long long)a+1;}
        }
        long long ceva=rez;
        cout<<ceva<<"\n";
    }
    return 0;
}
