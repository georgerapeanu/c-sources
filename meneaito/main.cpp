#include <cstdio>
#include <bitset>
#include <unordered_set>
#define NMAX 200005
using namespace std;
///FILE *f=fopen("meneaito.in","r");
FILE *f;
FILE *g=fopen("meneaito.out","w");
int A[NMAX],B[NMAX],N;
bitset<NMAX> E;
unordered_set<int> S;
int ind;
char buffer[4096];
void readinit(char *c)
{
    f=fopen(c,"r");
    ind=4095;
}
char getch()
{
    ind++;
    if(ind==4096) {fread(buffer,1,4096,f);ind=0;}
    return buffer[ind];
}
int i32()
{
    char c=getch();
    while(!('0'<=c&&c<='9'))
        c=getch();
    int nr=0;
    while('0'<=c&&c<='9')
    {
        nr=nr*10+c-'0';
        c=getch();
    }
    return nr;
}
int main()
{
    readinit("meneaito.in");
    N=i32();
    for(int i=2;i<N;i++)
    {
        A[i]=i32();
    }
    for(int i=2;i<N;i++)
    {
        B[i]=i32();
        if(A[i]>i||i>B[i])  continue;
        int c=2*(B[i]-A[i]),r1,r2;
        r1=i-A[i];
        r2=B[i]-A[i]+B[i]-i;
        if(S.find(r1+c*NMAX)==S.end())
        {
            for(int t=r1;t<=NMAX-5;t+=c)
            {
                E[t]=1;
            }
            S.insert(r1+c*NMAX);
        }
        if(S.find(r2+c*NMAX)==S.end())
        {
            for(int t=r2;t<=NMAX-5;t+=c)
            {
                E[t]=1;
            }
            S.insert(r2+c*NMAX);
        }
    }
    int rez=-1;
    for(int i=0;i<=NMAX-5;i++)
        if(!E[i])
            {rez=i;break;}
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
