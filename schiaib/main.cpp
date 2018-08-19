#include <cstdio>
#define zeros(x) (x&(x^(x-1)))
using namespace std;
FILE *f=fopen("schi.in","r");
FILE *g=fopen("schi.out","w");
int AIB[30005];
int V[30005];
int rez[30005];
int N;
void update(int poz,int val)
{
    for(int i=poz;i<=N;i+=zeros(i))
        AIB[i]+=val;
}
int querry(int poz)
{
   int sum=0;
   for(int i=poz;i;i-=zeros(i))
        sum+=AIB[i];
   return sum;
}
int getpos(int val)
{
    int st=1,dr=N;
    while(st<dr)
    {
        int mid=(st+dr)/2;
        if(querry(mid)<val)
            st=mid+1;
        else
            dr=mid;
    }
    update(st,-1);
    return st;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {fscanf(f,"%d",&V[i]);update(i,1);}
    for(int i=N;i;i--)
    {
        rez[getpos(V[i])]=i;
    }
    for(int i=1;i<=N;i++)
        fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
