#include <iostream>
#include <cmath>
using namespace std;
int p[1000005];
int N,nr1,nr2;
long long A[1000005];
long long B[1000005];
long long init;
long long eval(long long perm)
{
    long long rez=0;
    for(long long i=1;i<=N;i++)
    {
        int ind=i+perm;
        ind=(ind-1)%N+1;
        rez+=abs(ind-p[i]);
    }
    return rez;
}
int cand(int i,int pos)///dupa cate rotatii ajunge i pe pozitia pos
{
    if(i<=pos)return pos-i;
    return N-i+pos;
}
void addprog(int st,int dr,int p,int q)
{
    A[st]+=p;
    A[dr+1]-=p;
    A[st]-=q*st;
    A[dr+1]+=q*st;
    B[st]+=q;
    B[dr+1]-=q;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>p[i];
        if(p[i]>=i)
        {
            addprog(0,p[i]-i,p[i]-i,-1);
            addprog(p[i]-i+1,N-i,1,1);
            addprog(N-i+1,N-1,p[i]-1,-1);
        }
        else
        {
            addprog(0,N-i,i-p[i],1);
            addprog(N-i+1,N-i+p[i],p[i]-1,-1);
            addprog(N-i+p[i]+1,N-1,1,1);
        }
    }
    for(int i=1;i<=N;i++)
    {
        A[i]+=A[i-1];
        B[i]+=B[i-1];
    }
    long long rez=1LL<<60,poz;
    for(int i=0;i<N;i++)
    {
        if(rez>A[i]+B[i]*i){rez=A[i]+B[i]*i;poz=i;}
    }
    cout<<rez<<" "<<poz;
    return 0;
}
