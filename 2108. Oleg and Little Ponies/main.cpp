#include <cstdio>
#include <bitset>
#define NMAX 4001
#define MMAX 1001
using namespace std;
int urm[NMAX];
bitset <MMAX> A[NMAX],B[NMAX],x;
int tmp;
char a[MMAX],b[MMAX];
int N,M;
int main()
{
    scanf("%d %d\n",&M,&N);
    for(int i=1;i<=N;i++)
    {
        urm[i-1]=i;
        scanf("%s %s\n",a+1,b+1);
        for(int j=1;j<=M;j++)
        {
            A[i][j]=a[j]-'0';
            B[i][j]=b[j]-'0';
        }
    }
    gets(a+1);
    for(int i=1;i<=M;i++)
        x[i]=a[i]-'0';
    bool ceva;
    do
    {
        ceva=0;
        for(int i=0;urm[i];i=urm[i])
        {
            while(urm[i]&&((x&A[urm[i]])==A[urm[i]]))
            {
                x|=B[urm[i]];
                urm[i]=urm[urm[i]];
                ceva=1;
            }
        }
    }
    while(ceva);
    for(int i=1;i<=M;i++)
        {tmp=x[i];printf("%d",tmp);}
    return 0;
}
