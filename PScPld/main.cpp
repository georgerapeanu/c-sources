#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f=fopen("pscpld.in","r");
FILE *g=fopen("pscpld.out","w");
char A[1000005];
char B[2000005];
int L[2000005];
int N;
int id,i;
long long rez;
int main()
{
    fgets(A+1,1000005,f);
    N=strlen(A+1);N=N-(A[N]=='\n');
    for(int i=1;i<=N;i++)
    {
        B[2*i-1]='#';
        B[2*i]=A[i];
    }
    B[N=2*N+1]='#';
    id=0;

    for(int i=1;i<=N;i++)
    {
        if(id+L[id]>=i)L[i]=min(L[2*id-i],id+L[id]-i);
        while(i-L[i]-1>0&&i+L[i]+1<=N&&B[i-L[i]-1]==B[i+L[i]+1])L[i]++;
        if(id+L[id]<i+L[i])id=i;
        rez+=(1+L[i])/2;
        //fprintf(g,"%d ",L[i]);
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
