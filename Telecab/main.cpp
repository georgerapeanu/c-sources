#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
FILE *f=fopen("telecab.in","r");
FILE *g=fopen("telecab.out","w");
int H[100005];
int nxt[100005];
int ruc[100005];
int nr,dim;
stack<int> D;
int V[100005];
int N,K,S;
int lung,timp;
int dp[1005][1005];
long long sq(int nr)
{
    return 1LL*nr*nr;
}
int main()
{
    fscanf(f,"%d %d %d",&N,&K,&S);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&H[i]);
    D.push(N);
    for(int i=N-1;i;i--)
    {
        while(!D.empty()&&H[i]>=H[D.top()])D.pop();
        if(D.empty())nxt[i]=i+1;
        else nxt[i]=D.top();
        D.push(i);
    }
    for(int i=1;i;i=nxt[i])V[++nr]=i;
    for(int i=1;i<nr;i++)
        lung+=int(sqrt(1LL*sq(H[V[i]]-H[V[i+1]])+sq(V[i+1]-V[i])));
    for(int i=1;i<=nr;i++)
    {
        if(i!=1)
        {
            if(H[V[i-1]]<H[V[i]]){S-=(H[V[i]]-H[V[i-1]]);timp+=int(sqrt(sq(H[V[i]]-H[V[i-1]])+sq(V[i-1]-V[i])));}
            else ruc[++dim]=int(sqrt(sq(H[V[i]]-H[V[i-1]])+sq(V[i-1]-V[i])));
        }
        if(V[i]>=K){K=i;break;}
    }
    for(int i=1;i<=dim;i++)
    {
        for(int j=0;j<=S;j++)
        {
            dp[i][j]=min(dp[i-1][j]+ruc[i],(j-ruc[i]>=0 ? dp[i-1][j-ruc[i]]+1:(1<<30)));
        }
    }
    fprintf(g,"%d\n%d",lung,timp+dp[dim][S]);
    fclose(f);
    fclose(g);
    return 0;
}
