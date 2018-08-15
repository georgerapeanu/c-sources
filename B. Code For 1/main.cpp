#include <iostream>
#define LL long long
using namespace std;
LL rez=0;
LL lg2(LL nr)
{
    LL x=-1;
    while(nr)
    {
        nr>>=1;
        x++;
    }
    return x;
}
LL sizeofnr(LL nr)
{
    return  (1LL<<(lg2(nr)+1))-1;
}
void q(LL nr,LL l,LL r)
{
    LL len=sizeofnr(nr),halflen=len/2;
    if(len<=1){rez+=nr;return ;}
    if(l<=halflen)
        q(nr/2,l,min(halflen,r));
    if(l<=halflen+1&&r>=halflen+1)
        q(nr%2,halflen+1,halflen+1);
    if(r>halflen+1)
        q(nr/2,max(halflen+2,l)-halflen-1,r-halflen-1);
}
int main()
{
    LL N,l,r;
    cin>>N>>l>>r;
    q(N,l,r);
    cout<<rez;
    return 0;
}
