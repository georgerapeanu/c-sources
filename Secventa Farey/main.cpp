#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("farey.in","r");
FILE *g=fopen("farey.out","w");
int V[20];
int N,K;
struct frac{
    int x,y;
};
bool operator <=(frac a,frac b)
{
    return 1LL*a.x*b.y<=1LL*a.y*b.x;
}
bool operator <(frac a,frac b)
{
    return 1LL*a.x*b.y<1LL*a.y*b.x;
}
frac ceva[40005];
int len;
int pinex(int A,int B)
{
    V[0]=0;
    for(int i=2;i*i<=B;i++)
    {
        if(B%i==0)
        {
            V[++V[0]]=i;
            while(B%i==0)B/=i;
        }
    }
    int rez=0;
    for(int i=0;i<(1<<V[0]);i++)
    {
        int sgn=1,x=1;
        for(int j=0;j<V[0];j++)
        {
            if((i>>j)&1)
            {
                sgn*=-1;
                x*=V[j+1];
            }
        }
        rez+=sgn*(A/x);
    }
    return rez;
}
int tmp[40005];
int ok(int a)
{
    memset(tmp,0,sizeof(tmp));
    int val=0;
    for(int i=2;i<=N;i++)
    {
        int x=a*i/N;
        tmp[i]+=x;
        for(int j=i+i;j<=N;j+=i)tmp[j]-=tmp[i];
        val+=tmp[i];
    }
    return val;
}
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    int st=1,dr=N;
    while(dr-st>1)
    {
        double mid=(st+dr)/2;
        if(ok(mid)<=K)st=mid;
        else dr=mid;
    }
    K-=ok(st);
    frac a,b;a.x=st;b.x=dr;a.y=b.y=N;
    for(int i=1;i<=N;i++)
    {
        frac tmp;
        tmp.x=st*i/N;tmp.y=i;
        if(a<=tmp&&tmp<=b&&gcd(tmp.x,tmp.y)==1)ceva[++len]=tmp;
        tmp.x++;
        if(a<=tmp&&tmp<=b&&gcd(tmp.x,tmp.y)==1)ceva[++len]=tmp;
    }
    sort(ceva+1,ceva+1+len);
    fprintf(g,"%d %d",ceva[K+1].x,ceva[K+1].y);
    fclose(f);
    fclose(g);
    return 0;
}
