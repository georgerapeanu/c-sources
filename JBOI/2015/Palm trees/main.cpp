#include <iostream>
using namespace std;
int N,M,x,y,T;
int AINT[800005][2][2];
int t[800005][2];
int dr[800005];
int V[200005];
int tmp1[2];
int tmp2[2];
struct data{int a[2][2];};
string a;
data combina(int t1,int t2,int mid,data a,data b)
{
    data c;c.a[0][0]=c.a[0][1]=c.a[1][0]=c.a[1][1]=0;
    if(t1==-1&&t2==-1&&V[mid]==V[mid+1])
    {
        for(int i=0;i<2;i++)c.a[i][i]=0;
        for(int i=0;i<2;i++)c.a[i][1-i]=1;
        return c;
    }
    else if(t1==-1)
    {
        if(V[mid]==V[mid+1])return b;
    }
    else if(t2==-1)
    {
        if(V[mid]==V[mid+1])return a;
    }
    if(V[mid]<V[mid+1])
    {
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)c.a[i][j]=a.a[i][0]+b.a[0][j];
    }
    else if(V[mid]>V[mid+1])
    {
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)c.a[i][j]=a.a[i][1]+b.a[1][j];
    }
    else
    {
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)c.a[i][j]=a.a[i][t2]+b.a[t1][j]-(t1!=t2);
    }
    return c;
}
pair<int,int> tendinta(int a[],int b[],int mid)
{
    pair<int,int> rez;
    if(a[0]!=-1)rez.first=a[0];
    else if(V[mid]!=V[mid+1])rez.first=(V[mid]>V[mid+1]);
    else rez.first=b[0];
    if(b[1]!=-1)rez.second=b[1];
    else if(V[mid]!=V[mid+1])rez.second=(V[mid]>V[mid+1]);
    else rez.second=a[1];
    return rez;
}
void u(int nod,int st,int dr,int pos,int val)
{
    if(st==dr)
    {
        V[pos]=val;
        t[nod][0]=t[nod][1]=-1;
        for(int i=0;i<2;i++)AINT[nod][i][i]=0;
        for(int i=0;i<2;i++)AINT[nod][i][1-i]=1;
        return ;
    }
    int mid=(st+dr)/2;
    if(pos<=mid)u(nod*2,st,mid,pos,val);
    else u(2*nod+1,mid+1,dr,pos,val);
    pair<int,int> tmp=tendinta(t[2*nod],t[nod*2+1],mid);
    t[nod][0]=tmp.first;t[nod][1]=tmp.second;
    data a,b,c;
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)a.a[i][j]=AINT[2*nod][i][j];
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)b.a[i][j]=AINT[2*nod+1][i][j];
    c=combina(t[2*nod][1],t[2*nod+1][0],mid,a,b);
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)AINT[nod][i][j]=c.a[i][j];
}
pair<data,pair<int,int> > q(int nod,int st,int dr,int S,int D)
{
    if(S<=st&&dr<=D)
    {
        data c;
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)c.a[i][j]=AINT[nod][i][j];
        return {c,{t[nod][0],t[nod][1]}};
    }
    int mid=(st+dr)/2;
    if(D<=mid)return q(2*nod,st,mid,S,D);
    if(S>mid)return q(2*nod+1,mid+1,dr,S,D);
    pair<data,pair<int,int> > a,b;
    a=q(2*nod,st,mid,S,D);
    b=q(2*nod+1,mid+1,dr,S,D);
    data c=combina(a.second.second,b.second.first,mid,a.first,b.first);
    tmp1[0]=a.second.first;tmp1[1]=a.second.second;
    tmp2[0]=b.second.first;tmp2[1]=b.second.second;
    pair<int,int> tmp=tendinta(tmp1,tmp2,mid);
    return {c,tmp};
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        int val;
        cin>>val;
        u(1,1,N,i,val);
    }
    for(int i=1;i<=M;i++)
    {
        cin>>a>>x>>y;
        if(a=="REPLACE")u(1,1,N,x,y);
        else
        {
            data c=q(1,1,N,x,y).first;
            int val=max(max(c.a[0][0],c.a[0][1]),max(c.a[1][0],c.a[1][1]));
            cout<<(y-x+1)-val<<"\n";
        }
    }
    return 0;
}
