#include <iostream>
#include <cstdlib>
#include <set>
#include <cstdio>
#define x first
#define y second
using namespace std;
string a,b;
pair<int,int> H,A[3],MOD;
pair<int,int> V[5005];
int i,j;
bool used[3];
pair<int,int> lgpow(pair<int,int> b,int e)
{
    pair<int,int> p={1,1};
    while(e)
    {
        if(e&1)p={(1LL*p.x*b.x)%MOD.x,(1LL*p.y*b.y)%MOD.y};
        b={(1LL*b.x*b.x)%MOD.x,(1LL*b.y*b.y)%MOD.y};
        e>>=1;
    }
    return p;
}
int len[3];
int ord[3];
struct data
{
    pair<int,int> a,b,c;
};
bool operator < (data a,data b)
{
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
    if(a.c!=b.c) return a.c<b.c;
}
set<data> S;
void build(string b,bool op)
{
    for(int i=b.size()-1;i>=0;i--)
    {
        pair<int,int> tmp=lgpow({26,26},b.size()-1-i);
        V[i]={(1LL*tmp.x*(b[i]-'a')+V[i+1].x)%MOD.x,(1LL*tmp.y*(b[i]-'a')+V[i+1].y)%MOD.y};
    }
    A[0]={0,0};
    for(i=0;i<b.size()-2;i++)
    {
        A[0]={(1LL*A[0].x*26+b[i]-'a')%MOD.x,(1LL*A[0].y*26+b[i]-'a')%MOD.y};
        A[1]={0,0};
        for(j=i+1;j<b.size()-1;j++)
        {
            A[1]={(1LL*A[1].x*26+b[j]-'a')%MOD.x,(1LL*A[1].y*26+b[j]-'a')%MOD.y};
            A[2]=V[j+1];
            len[0]=i+1;
            len[1]=j-i;
            len[2]=b.size()-j-1;
            if(op==0)
            {
                data tmp={A[0],A[1],A[2]};
                S.insert(tmp);
            }
            else
            {
                data tmp={A[0],A[1],A[2]};
                if(S.find(tmp)!=S.end()){cout<<"YES\n";cout<<b.substr(0,len[0])<<"\n"<<b.substr(len[0],len[1])<<"\n"<<b.substr(len[0]+len[1],len[2]);exit(0);}
                else if(S.find({A[0],A[2],A[1]})!=S.end()){cout<<"YES\n";cout<<b.substr(0,len[0])<<"\n"<<b.substr(len[0]+len[1],len[2])<<"\n"<<b.substr(len[0],len[1]);exit(0);}
                else if(S.find({A[1],A[0],A[2]})!=S.end()){cout<<"YES\n";cout<<b.substr(len[0],len[1])<<"\n"<<b.substr(0,len[0])<<"\n"<<b.substr(len[0]+len[1],len[2]);exit(0);}
                else if(S.find({A[1],A[2],A[0]})!=S.end()){cout<<"YES\n";cout<<b.substr(len[0],len[1])<<"\n"<<b.substr(len[0],len[1])<<"\n"<<b.substr(0,len[0]);exit(0);}
                else if(S.find({A[2],A[0],A[1]})!=S.end()){cout<<"YES\n";cout<<b.substr(len[0]+len[1],len[2])<<"\n"<<b.substr(0,len[0])<<"\n"<<b.substr(len[0],len[1]);exit(0);}
                else if(S.find({A[2],A[1],A[0]})!=S.end()){cout<<"YES\n";cout<<b.substr(len[0]+len[1],len[2])<<"\n"<<b.substr(len[0],len[1])<<"\n"<<b.substr(0,len[0]);exit(0);}
            }
        }
    }
}
int main()
{
    MOD={666013,123456};
    ///freopen("k.in","r",stdin);
    cin>>a>>b;
    if(a.size()!=b.size()||a.size()<3){cout<<"NO";return 0;}
    build(a,0);
    build(b,1);
    cout<<"NO";
    return 0;
}
