#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
FILE *f=fopen("bleach.in","r");
FILE *g=fopen("bleach.out","w");
int N,K;
int val;
priority_queue<int,vector<int>,greater<int> > H;
long long act,s;
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N&&i<=2*K;i++)
        {fscanf(f,"%d",&val);H.push(val);}
    for(int i=2*K+1;i<=N;i++)
    {
        int t=H.top();H.pop();
        fscanf(f,"%d",&val);H.push(val);
        if(act<t)
        {
            s+=t-act;
            act=t;
        }
        act+=t;
    }
    while(!H.empty())
    {
        int t=H.top();H.pop();
        if(act<t)
        {
            s+=t-act;
            act=t;
        }
        act+=t;
    }
    fprintf(g,"%d",s);
    fclose(f);
    fclose(g);
    return 0;
}
