#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
FILE *f=fopen("strmatch.in","r");
FILE *g=fopen("strmatch.out","w");
int F[2000005],N,M;
char A[2000005];
char B[2000005];
vector<int> V;
int nr;
int kmp()
{
    F[1]=0;
    for(int i=2;i<=N;i++)
    {
        int k=F[i-1];
        while(k&&A[k+1]!=A[i])k=F[k];
        if(A[k+1]==A[i])k++;
        F[i]=k;
    }
    int j=0;
    for(int i=1;i<=M;i++)
    {
        while(j&&A[j+1]!=B[i])j=F[j];
        if(A[j+1]==B[i])j++;
        if(j==N)
        {
            j=F[j];
            nr++;
            if(nr>1000)continue;
            V.push_back(i-N);
        }
    }
    return j;
}
int main()
{
    fgets(A+1,2000005,f);N=strlen(A+1);N-=(A[N]=='\n');
    fgets(B+1,2000005,f);M=strlen(B+1);M-=(B[M]=='\n');
    kmp();
    fprintf(g,"%d\n",nr);
    for(auto it:V)
        fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
