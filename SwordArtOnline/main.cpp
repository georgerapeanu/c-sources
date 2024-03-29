#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
FILE *f=fopen("sao.in","r");
FILE *g=fopen("sao.out","w");
int N,K,i;
long long HP,val;
priority_queue <long long> H;
int main()
{
    fscanf(f,"%d %d %lld",&N,&K,&HP);
    for(i=1;i<=N&&HP>0;i++)
    {
        fscanf(f,"%lld",&val);
        HP-=val;
        H.push(val);
        if(HP<=0&&K&&H.top()>0 )
        {
            K--;
            HP+=H.top();
            H.pop();
        }
    }
    i--;
    if(HP<0)
        i--;
    fprintf(g,"%d",i);
    fclose(f);
    fclose(g);
    return 0;
}
