#include <cstdio>
#define MOD 9917
using namespace std;
FILE *f=fopen("inv.in","r");
FILE *g=fopen("inv.out","w");
int V[100005];
int tmp[100005];
int inv;
int N;
void msort(int st,int dr)
{
    if(st==dr)
        return ;
    int mid=(st+dr)/2;
    msort(st,mid);
    msort(mid+1,dr);
    int i,j;
    i=st;j=mid+1;
    int ind=st;
    while(i<=mid&&j<=dr)
    {
        if(V[i]<=V[j])
        {
            tmp[ind++]=V[i++];
            inv=(inv+j-mid-1)%MOD;
        }
        else
            tmp[ind++]=V[j++];
    }
    while(i<=mid)
    {
        tmp[ind++]=V[i++];
        inv=(inv+dr-mid)%MOD;
    }
    while(j<=dr)
        tmp[ind++]=V[j++];
    for(int i=st;i<=dr;i++)
        V[i]=tmp[i];
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&V[i]);
    msort(1,N);
    fprintf(g,"%d",inv);
    fclose(f);
    fclose(g);
    return 0;
}
