#include <cstdio>
#define NMAX 100005
using namespace std;
FILE *f=fopen("prefix2.in","r");
FILE *g=fopen("prefix2.out","w");
int F[NMAX];///hai cu kmp-ul
char A[NMAX];
int main()
{
    fgets(A+1,NMAX,f);
    int N=strlen(A+1);
    for(int i=2;i<=N;i++)
    {
        int k=F[i-1];
        while(k&&A[k])
    }
    return 0;
}
