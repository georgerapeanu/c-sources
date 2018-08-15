#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("nrsubsecv.in","r");
FILE *g=fopen("nrsubsecv.out","w");
int N,M;
int st[1000005];
int dr[1000005],x,y;
stack<int> S,D;
int V[1000005];
long long rez[1000005];
int main()
{
    fscanf(f,"%d%d",&N,&M);
    S.push(0);
    D.push(N+1);
    V[0]=V[N+1]=-1;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        ++V[i];
        while(V[i]<V[S.top()]) S.pop();
        st[i]=S.top();
        S.push(i);
    }
    for(int i=N;i;i--)
    {
        while(V[i]<=V[D.top()])
            D.pop();
        dr[i]=D.top();
        D.push(i);
    }
    for(int i=1;i<=N;i++)
    {
        rez[V[i]]+=1LL*(i-st[i])*(dr[i]-i);
    }
    for(int i=1;i<=1000001;i++)
        rez[i]+=rez[i-1];
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&x,&y);
        ++x;
        ++y;
        fprintf(g,"%lld\n",rez[y]-rez[x-1]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
