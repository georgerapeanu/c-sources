#include <cstdio>
#include <algorithm>
#define zeros(x) (x&(x^(x-1)))
using namespace std;
FILE *f=fopen("inversiuni.in","r");
FILE *g=fopen("inversiuni.out","w");
int AIB[200001];
int val,N;
long long rez;
void update(int poz,int val)
{
    for(int i=poz;i<=200001;i+=zeros(i))
        AIB[i]+=val;
}
int query(int poz)
{
    int sum=0;
    for(int i=poz;i;i-=zeros(i))
        sum+=AIB[i];
    return sum;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        rez+=min(query(val),query(N)-query(val));
        update(val,1);
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
