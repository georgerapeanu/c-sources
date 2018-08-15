#include <iostream>
#include <cstdio>

using namespace std;
/*int cf[]={0,2,3,5,7};
bool u[5];
int nr=0;
void btr(int pas,int nrcf)
{
    if(pas>nrcf)
    {
        cout<<nr<<"\n";return ;
    }
    for(int i=1;i<=4;i++)
    {
        if(u[i]) continue;
        nr=nr*10+cf[i];u[i]=1;
        btr(pas+1,nrcf);
        nr/=10;u[i]=0;
    }
}*/
int num[]={2,
3,
5,
7,
23,
37,
53,
73
};
int main()
{
    ///freopen("1.out","w",stdout);
    ///for(int i=1;i<=4;i++)btr(1,i);
    int a,b,nr=0;
    cin>>a>>b;
    for(int i=0;i<8;i++)
        if(num[i]>=a&&num[i]<=b) nr++;
    cout<<nr;
    return 0;
}
