#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>
#define LEN 10000
using namespace std;
FILE *f=fopen("easychoice.in","r");
FILE *g=fopen("easychoice.out","w");
int N,R,C;
int V[1000005];
int A[1000005];
int DP[1000005];
char buff[LEN];
int ind=LEN-1;
int i32()
{
    int nr=0;
    while(buff[ind]<'0'||buff[ind]>'9')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return nr;
}
bool ok(int val)
{
    memset(DP,0,sizeof(DP));
    for(int i=1;i<=N;i++)
        DP[i]=max(DP[i-1],(i-C+1>0&&V[i]-V[i-C+1]<=val ? DP[i-C]+1:0));
    return DP[N]>=R;
}
int main()
{
    N=i32();R=i32();C=i32();
    if(C==1){fputs("0",g);return 0;}
    for(int i=1;i<=N;i++)
    {
        V[i]=i32();
    }
    sort(V+1,V+1+N);
    int st=1,dr=1000000000;
    while(st<dr)
    {
        int mid=(st+dr)>>1;
        if(ok(mid))
            dr=mid;
        else
            st=mid+1;
    }
    fprintf(g,"%d",st);
    fclose(f);
    fclose(g);
    return 0;
}
