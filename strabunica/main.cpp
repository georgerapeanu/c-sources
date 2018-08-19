#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("strabunica.in","r");
FILE *g=fopen("strabunica.out","w");
long long N,i,st[200005],dr[200005],V[200005];
long long maxim;
stack <long long> S,D;
int main()
{
    fscanf(f,"%lld",&N);
    S.push(0);
    D.push(N+1);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V[i]);
    }
    for(i=1;i<=N;i++)
    {
        while(V[i]<=V[S.top()])
            S.pop();
        st[i]=S.top();
        S.push(i);
        while(V[N-i+1]<=V[D.top()])
            D.pop();
        dr[N-i+1]=D.top();
        D.push(N-i+1);
    }
    for(i=1;i<=N;i++)
    {
        if(V[i]*(dr[i]-st[i]-1)>maxim)
            maxim=V[i]*(dr[i]-st[i]-1);
    }
    fprintf(g,"%lld",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
