#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("buget.in","r");
FILE *g=fopen("buget.out","w");
int N;
long long B;
int P[100005];
bool ch(int val)
{
    long long rez=0;
    for(int i=1;i<=N;i++)
        rez+=min(P[i],val);
    return (rez<=B);
}
int main()
{
    fscanf(f,"%d%lld",&N,&B);
    for(int i=1;i<=N;i++) fscanf(f,"%d",&P[i]);
    int rez=0;
    for(int i=(1<<30);i;i>>=1)
        if(ch(rez+i))
            rez+=i;
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
