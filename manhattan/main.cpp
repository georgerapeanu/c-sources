#include <iostream>
#include <cstdio>
#define MOD 666013
using namespace std;
struct zona
{
    int X[3];
    int Y[3];
}Z[3];
int adun(int a,int b)
{
    a+=b;
    if(a>=MOD)a-=MOD;
    return a;
}
int scad(int a,int b)
{
    a-=b;
    if(a<0)a+=MOD;
    return a;
}
int mult(int a,int b)
{
    return 1LL*a*b%MOD;
}
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=mult(p,b);
        b=mult(b,b);
        e>>=1;
    }
    return p;
}
int fact[500005];
int ifact[500005];
int C(int N,int K)
{
    if(K<0||K>N||N<0)return 0;
    return mult(fact[N],mult(ifact[K],ifact[N-K]));
}
const int dada=0;
int orizontala(int x1,int x2,int y,zona Z)
{
    Z.Y[1]-=y;
    Z.Y[2]-=y;
    y=0;
    if(Z.Y[2]<0)
    {
        Z.Y[1]*=-1;
        Z.Y[2]*=-1;
        swap(Z.Y[1],Z.Y[2]);
    }
    if(Z.Y[1]<0)
    {
        int y1=Z.Y[1],y2=Z.Y[2];
        Z.Y[1]=0;Z.Y[2]=-y1;
        int ans=orizontala(x1,x2,y,Z);
        Z.Y[2]=y2;Z.Y[1]++;
        if(Z.Y[1]<=Z.Y[2])ans=adun(ans,orizontala(x1,x2,y,Z));
        return ans;
    }
    ///lets test it
    int ans=0;
    if(dada)
    {
        for(int x=x2;x>=x1;x--)
        {
            int X2=Z.X[2]-x,X1=Z.X[1]-x;
            int l=Z.Y[2]-Z.Y[1],Y=Z.Y[1];
            ans=adun(ans,scad(scad(C(X2+Y+l+2,X2+1),C(X1+Y+l+1,X1)),scad(C(X2+Y+1,X2+1),C(X1+Y,X1))));
        }
    }
    else
    {
        int X2=Z.X[2]-x2,X1=Z.X[1]-x2;
        int l=Z.Y[2]-Z.Y[1];
        int Y=Z.Y[1];
        int off=x2-x1;
        ans=scad(scad(scad(C(X2+Y+l+off+3,X2+off+1),C(X2+Y+l+2,X2)),scad(C(X1+Y+l+off+2,X1+off),C(X1+Y+l+1,X1-1))),scad(scad(C(X2+Y+off+2,X2+off+1),C(X2+Y+1,X2)),scad(C(X1+off+Y+1,X1+off),C(X1+Y,X1-1))));
    }
    return ans;
}
int main()
{
    freopen("manhattan.in","r",stdin);
    freopen("manhattan.out","w",stdout);
    fact[0]=1;for(int i=1;i<=500000;i++)fact[i]=mult(fact[i-1],i);
    ifact[500000]=lgpow(fact[500000],MOD-2);
    for(int i=500000-1;i>=0;i--)ifact[i]=mult(ifact[i+1],i+1);
    for(int i=1;i<3;i++)for(int j=1;j<3;j++)cin>>Z[i].X[j]>>Z[i].Y[j];
    if(Z[1].X[1]>Z[2].X[1])swap(Z[1],Z[2]);
    if(Z[1].X[2]>=Z[2].X[1]&&Z[1].X[1]<=Z[2].X[2])
    {
        if(Z[1].Y[1]<=Z[2].Y[1])
        {
            Z[1].X[1]*=-1;swap(Z[1].X[1],Z[1].Y[1]);
            Z[1].X[2]*=-1;swap(Z[1].X[2],Z[1].Y[2]);
            Z[2].X[1]*=-1;swap(Z[2].X[1],Z[2].Y[1]);
            Z[2].X[2]*=-1;swap(Z[2].X[2],Z[2].Y[2]);
            if(Z[1].X[1]>Z[1].X[2])swap(Z[1].X[1],Z[1].X[2]);
            if(Z[1].Y[1]>Z[1].Y[2])swap(Z[1].Y[1],Z[1].Y[2]);
            if(Z[2].X[1]>Z[2].X[2])swap(Z[2].X[1],Z[2].X[2]);
            if(Z[2].Y[1]>Z[2].Y[2])swap(Z[2].Y[1],Z[2].Y[2]);
        }
        else
        {
            Z[1].Y[1]*=-1;swap(Z[1].X[1],Z[1].Y[1]);
            Z[1].Y[2]*=-1;swap(Z[1].X[2],Z[1].Y[2]);
            Z[2].Y[1]*=-1;swap(Z[2].X[1],Z[2].Y[1]);
            Z[2].Y[2]*=-1;swap(Z[2].X[2],Z[2].Y[2]);
            if(Z[1].X[1]>Z[1].X[2])swap(Z[1].X[1],Z[1].X[2]);
            if(Z[1].Y[1]>Z[1].Y[2])swap(Z[1].Y[1],Z[1].Y[2]);
            if(Z[2].X[1]>Z[2].X[2])swap(Z[2].X[1],Z[2].X[2]);
            if(Z[2].Y[1]>Z[2].Y[2])swap(Z[2].Y[1],Z[2].Y[2]);
        }
    }
    int rez=0;
    for(int i=Z[1].Y[1];i<=Z[1].Y[2];i++)
    {
        rez=adun(rez,orizontala(Z[1].X[1],Z[1].X[2],i,Z[2]));
    }
    cout<<rez;
    return 0;
}
