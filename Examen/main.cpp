#include <cstdio>
using namespace std;
FILE *f=fopen("examen.in","r");
FILE *g=fopen("examen.out","w");
int N;
int S[100005];
int V[100005];
bool ok1(int val)
{
    V[1]=val;
    for(int i=3;i<=N;i+=2)
    {
        V[i]=S[i-1]-V[i-2];
    }
    for(int i=2;i<=N;i+=2)
    {
        V[i]=S[i-1]-V[(N+i-3)%N+1];
    }
    return V[1]<S[N]-V[N-1];
}
bool ok2(int val,int p)
{
    V[p]=val;
    for(int i=p+2;i<=N;i++)
    {
        V[i]=S[i-1]-V[i-2];
    }
    return V[p]<S[(p-2+N)%N+1]-V[(p-3+N)%N+1];
}
bool ok(int val,int p)
{
    if(N%2==1)
        return ok1(val);
    return ok2(val,p);
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&S[i]);
    }
    if(N%4==0)
    {
        fprintf(g,"-1");fclose(f);fclose(g);return 0;
    }
    int st=-1000000000,dr=1000000000;
    while(dr-st>1)
    {
        int mid=(st+dr)/2;
        if(ok(mid,1))
            st=mid;
        else
            dr=mid;
    }
    ok(dr,1);
    if(N%2==0)
    {
        int st=-1000000000,dr=1000000000;
        while(dr-st>1)
        {
            int mid=(st+dr)/2;
            if(ok(mid,2))
                st=mid;
            else
                dr=mid;
        }
        ok(dr,2);
    }
    for(int i=1;i<=N;i++)
        fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
