#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
FILE *f=fopen("nucleulvaloros.in","r");
FILE *g=fopen("nucleulvaloros.out","w");
int T,K,N;
int V[50001];
int rez[50001];
deque<int> D;
bool eval()
{
    D.clear();
    for(int i=1;i<K;i++)
    {
        while(!D.empty()&&rez[D.back()]<rez[i])
            D.pop_back();
        D.push_back(i);
    }
    for(int i=1;i<=N-K+1;i++)
    {
        while(!D.empty()&&D.front()<i) D.pop_front();
        while(!D.empty()&&rez[D.back()]<rez[i+K-1]) D.pop_back();
        D.push_back(i+K-1);
        if(V[i]!=rez[D.front()])
            return 0;
    }
    return 1;
}
void solve()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N-K+1;i++)
        fscanf(f,"%d",&V[i]);
    D.clear();
    for(int i=1;i<=N;i++)
    {
        while(!D.empty()&&D.front()<=i-K)
            D.pop_front();
        if(i<=N-K+1)
        {
            while(!D.empty()&&V[D.back()]>V[i])
                D.pop_back();
            D.push_back(i);
        }
        rez[i]=V[D.front()];
    }
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        solve();
        if(!eval())
            fprintf(g,"-1");
        else
            for(int i=1;i<=N;i++) fprintf(g,"%d ",rez[i]);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
