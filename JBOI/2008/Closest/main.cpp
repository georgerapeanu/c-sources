#include <cstdio>
#include <cstring>
using namespace std;
int frecv[10];
int C[66];
int A[66];
int B[66];
int N;
int gmax()
{
    int cf=9;
    while(!frecv[cf])cf--;
    return cf;
}
int gmin()
{
    int cf=0;
    while(!frecv[cf])cf++;
    return cf;
}
void umplecresc(int i,int N)
{
    int cf=gmin();
    for(;i<N;i++)
    {
        C[i]=cf;
        frecv[cf]--;
        while(!frecv[cf])cf++;
    }
    C[N]=cf;
}
void umpledecresc(int i,int N)
{
    int cf=gmax();
    for(;i<N;i++)
    {
        C[i]=cf;
        frecv[cf]--;
        while(!frecv[cf])cf--;
    }
    C[N]=cf;
}
bool maimare(int i,int N)
{
    if(i>N)return 1;
    if(frecv[A[i]]==0)
    {
        if(gmax()<A[i])return 0;
        int cf=A[i]+1;
        while(cf<10&&!frecv[cf])cf++;
        if(cf>=10)return 0;
        C[i]=cf;
        frecv[cf]--;
        umplecresc(i+1,N);
        return 1;
    }
    C[i]=A[i];
    frecv[A[i]]--;
    if(maimare(i+1,N))return 1;
    frecv[A[i]]++;
    if(gmax()<A[i])return 0;
    int cf=A[i]+1;
    while(cf<10&&!frecv[cf])cf++;
    if(cf>=10)return 0;
    C[i]=cf;
    frecv[cf]--;
    umplecresc(i+1,N);
    return 1;
}
bool maimic(int i,int N)
{
    if(i>N)return 0;
    if(frecv[A[i]]==0)
    {
        if(gmin()>A[i])return 0;
        int cf=A[i]-1;
        while(cf>=0&&!frecv[cf])cf--;
        if(cf==0&&i==1)return 0;
        if(cf<0)return 0;
        C[i]=cf;
        frecv[cf]--;
        umpledecresc(i+1,N);
        return 1;
    }
    C[i]=A[i];
    frecv[A[i]]--;
    if(maimic(i+1,N))return 1;
    frecv[A[i]]++;
    if(gmin()>A[i])return 0;
    int cf=A[i]-1;
    while(cf>=0&&!frecv[cf])cf--;
    if(cf==0&&i==1)return 0;
    if(cf<0)return 0;
    C[i]=cf;
    frecv[cf]--;
    umpledecresc(i+1,N);
    return 1;
}
char tmp[65];
int main()
{
    fgets(tmp+1,65,stdin);
    N=strlen(tmp+1);N-=(tmp[N]=='\n');
    for(int i=1;i<=N;i++)
    {
        A[i]=tmp[i]-'0';
    }
    fgets(tmp+1,65,stdin);
    for(int i=1;i<=N;i++)
    {
        B[i]=tmp[i]-'0';
    }
    for(int i=1;i<=N;i++)frecv[B[i]]++;
    if(!maimare(1,N))printf("0\n");
    else for(int i=1;i<=N;i++)printf("%d",C[i]);
    printf("\n");
    for(int i=0;i<10;i++)frecv[i]=0;
    for(int i=1;i<=N;i++)frecv[B[i]]++;
    if(!maimic(1,N))printf("0\n");
    else for(int i=1;i<=N;i++)printf("%d",C[i]);
    return 0;
}
