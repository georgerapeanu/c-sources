#include <iostream>
using namespace std;
long long N,T,K,V,Q;
long long fst(long long x,long long y,long long sz,long long N,long long pos)
{
  if(N==1)return pos;
  if(x>N/2)
  {
     x=N-x+1;
     pos=sz+sz-pos+1;
  }
  sz<<=1;
  if(y>N/2)
  {
      y=N-y+1;
      pos=sz+sz-pos+1;
  }
  sz<<=1;
  return fst(x,y,sz,N>>1,pos);
}
long long snd(long long pos,long long x,long long y,long long sz,long long N)
{
    if(sz==1)return 1LL*(x-1)*N+y;
    if(pos>sz/2)
    {
        pos=sz/2-(pos-sz/2)+1;
        y=N+N-y+1;
    }
    sz>>=1;
    if(pos>sz/2)
    {
        pos=sz/2-(pos-sz/2)+1;
        x=N+N-x+1;
    }
    sz>>=1;
    return snd(pos,x,y,sz,N<<1);
}
int main() {
    cin>>Q;
    while(Q--)
    {
        cin>>T>>K>>V;
        N=1LL<<K;
        if(T==1)cout<<fst(V/N+(V%N!=0),V%N+(V%N==0 ? N:0),1,N,1);
        else cout<<snd(V,1,1,1LL*N*N,1);
        cout<<"\n";
    }
    return 0;
}
