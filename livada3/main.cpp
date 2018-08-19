#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#define pb push_back
using namespace std;
FILE *f;
FILE *g=fopen("livada3.out","w");
int  A[105][25005];
long long S[105][25005];
int MA[105][25005];
int N,M;
long long C;
char buffer[4096];
int ind;
int R;
long long x,y,z,w,u;
int getcol(int linie,long long val)
{
    int st=0,dr=M;
    while(st<dr)
    {
        int mid=(st+dr+1)/2;
        if(MA[linie][mid]>val)
            dr=mid-1;
        else
            st=mid;
    }
    return st;
}
vector<long long> tmp;
bool ok(long long val)
{
    for(int i=1;i<=N;i++)
    {
        tmp[i-1]=S[i][getcol(i,val)];
    }
    long long nr=0;
    sort(tmp.begin(),tmp.end());
    int len=tmp.size();
    for(int i=len-1;i>=len-R;i--)
        nr+=tmp[i];
    if(nr>=C)
        return 1;
    return 0;
}
void readint(char *c)
{
    f=fopen(c,"r");
    ind=4095;
}
char getch()
{
    ind++;
    if(ind==4096)
    {
        ind=0;
        fread(buffer,1,4096,f);
    }
    return buffer[ind];
}
int i32()
{
    int nr=0;
    char c=getch();
    while(!isdigit(c))
        c=getch();
    while(isdigit(c))
    {
        nr=nr*10+c-'0';
        c=getch();
    }
    return nr;
}
long long i64()
{
    long long nr=0;
    char c=getch();
    while(!isdigit(c))
        c=getch();
    while(isdigit(c))
    {
        nr=nr*10+c-'0';
        c=getch();
    }
    return nr;
}
int main()
{
    readint("livada3.in");
    N=i32();M=i32();C=i64();R=i32();
    x=i64();y=i64();z=i64();w=i64();u=i64();
    tmp.resize(N);
    for(int i=1;i<=M;i++)
    {
        A[1][i]=i32();
        MA[1][i]=max(MA[1][i-1],A[1][i]);
        S[1][i]=A[1][i]+S[1][i-1];
    }
    for(int i=2;i<=N;i++)
    {
        A[i][1]=i32();
        MA[i][1]=S[i][1]=A[i][1];
    }
    for(int i=2;i<=N;i++)
    {
        for(int j=2;j<=M;j++)
        {
            A[i][j]=(x*A[i-1][j]+y*A[i][j-1]+z*A[i-1][j-1]+w)%u;
            S[i][j]=S[i][j-1]+A[i][j];
            MA[i][j]=max(MA[i][j-1],A[i][j]);
        }
    }
    long long st=1,dr=1000000000;
    while(st<dr)
    {
        long long mid=(st+dr)/2;
        if(ok(mid))
        {
            dr=mid;
        }
        else
            st=mid+1;
    }
    fprintf(g,"%lld",st);
    fclose(f);
    fclose(g);
    return 0;
}
