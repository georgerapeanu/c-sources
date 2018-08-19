#include <cstdio>
#include <algorithm>
#include <deque>
#define x first
#define y second
using namespace std;
FILE *f=fopen("palmieri.in","r");
FILE *g=fopen("palmieri.out","w");
int N,A,upos;
int dp[250005];
deque<int> D;
pair<int,int> V[250005];
int main()
{
    fscanf(f,"%d%d",&N,&A);
    for(int i=1;i<=N;i++) fscanf(f,"%d %d",&V[i].x,&V[i].y);
    sort(V+1,V+1+N);
    V[0].x=V[1].x-1;
    for(int i=1;i<=N;i++)
    {
        while(!D.empty()&&V[D.back()].y<=V[i].y)
            D.pop_back();
        D.push_back(i);
        while(!D.empty()&&1LL*V[D.front()].y*max(1,V[i].x-V[upos].x)>A)
        {
            upos++;
            if(D.front()<upos) D.pop_front();
        }
        dp[i]=dp[upos-1]+1;
    }
    fprintf(g,"%d",dp[N]);
    fclose(f);
    fclose(g);
    return 0;
}
