#include <iostream>
#include <cstring>
using namespace std;
int t[4000005];
int o[4000005];
int c[4000005];
char C[1000005];
int N,Q;
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        if(C[st]=='(')
        {
            o[nod]=1;
        }
        else
        {
            c[nod]=1;
        }
        return ;
    }
    build(2*nod,st,(st+dr)/2);
    build(2*nod+1,(st+dr)/2+1,dr);
    int tmp=min(o[2*nod],c[2*nod+1]);
    t[nod]=t[2*nod]+t[2*nod+1]+tmp;
    o[nod]=o[2*nod+1]+o[2*nod]-tmp;
    c[nod]=c[2*nod+1]+c[2*nod]-tmp;
}
struct ans{int t,o,c;};
ans q(int nod,int st,int dr,int S,int D)
{
    if(S<=st&&dr<=D)return {t[nod],o[nod],c[nod]};
    int mid=(st+dr)/2;
    if(D<=mid)return q(nod*2,st,mid,S,D);
    else if(S>mid)return q(nod*2+1,mid+1,dr,S,D);
    ans a,b;
    a=q(nod*2,st,mid,S,D);
    b=q(nod*2+1,mid+1,dr,S,D);
    int tmp=min(a.o,b.c);
    return {a.t+b.t+tmp,a.o+b.o-tmp,a.c+b.c-tmp};
}
int main()
{
    cin.getline(C+1,1000005);
    N=strlen(C+1);N-=(C[N]=='\n');
    build(1,1,N);
    cin>>Q;
    while(Q--)
    {
        int st,dr;
        cin>>st>>dr;
        cout<<2*q(1,1,N,st,dr).t<<"\n";
    }
    return 0;
}
