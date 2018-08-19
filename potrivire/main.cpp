#include <cstdio>
#include <vector>
#include <cctype>
#include <cstring>
#define BASE 26
#define M1 10003
#define M2 666013
using namespace std;
FILE *f=fopen("potrivire.in","r");
FILE *g=fopen("potrivire.out","w");
char A[10005];
char B[10005];
vector<int> V[35];
int N,M;
int st,dr,i,j,ant,lung[35],nrscv=1;
int imod (int a,int b)
{
    return (a%b+b)%b;
}
void srch(int st,int dr)
{
    int len=dr-st+1;
    int hv1=0,hv2=0,hvi1=0,hvi2=0;
    for(int i=st;i<=dr;i++)
    {
        hv1=imod(hv1*BASE+B[i]-'a',M1);
        hv2=imod(hv2*BASE+B[i]-'a',M2);
    }

    int E1=1,E2=1;
    for(int i=1;i<len;i++)
    {
        E1=imod(E1*BASE,M1);
        E2=imod(E2*BASE,M2);
    }
    for(int i=1;i<=len;i++)
    {
        hvi1=imod(hvi1*BASE+A[i]-'a',M1);
        hvi2=imod(hvi2*BASE+A[i]-'a',M2);
    }
    if(hvi1==hv1&&hvi2==hv2)
        V[nrscv].push_back(1);
    for(int i=len+1;i<=N;i++)
    {
        hvi1=imod(hvi1-imod(E1*(A[i-len]-'a'),M1),M1);
        hvi2=imod(hvi2-imod(E2*(A[i-len]-'a'),M2),M2);
        hvi1=imod(hvi1*BASE,M1);
        hvi2=imod(hvi2*BASE,M2);
        hvi1=imod(hvi1+A[i]-'a',M1);
        hvi2=imod(hvi2+A[i]-'a',M2);
        if(hvi1==hv1&&hvi2==hv2)
            V[nrscv].push_back(i-len+1);
    }
}
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    fgets(A+1,10001,f);
    fgets(B+1,10001,f);
    int j=1;
    while(j<=M)
    {
        while(j<=M&&B[j]=='*')
            j++;
        if(j<=M)
        {
            st=j;
            while(isalpha(B[j+1])&&j<M)
                j++;
            dr=j;
            srch(st,dr);
            lung[nrscv]=dr-st;
            nrscv++;
        }
        j++;
    }
    ant=0;
    for(int i=1;i<nrscv;i++)
    {
        int j=0,n=V[i].size();
        while(j<n&&V[i][j]<=ant)
            j++;
        if(j==n)
        {
            fprintf(g,"-1");
            return 0;
        }
        if(i==1)
            st=V[i][j];
        ant=V[i][j]+lung[i];
    }
    if(B[1]=='*')
        st=1;
    dr=ant;
    fprintf(g,"%d %d",st,dr);
    return 0;
}
