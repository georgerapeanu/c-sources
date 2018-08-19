#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("puzzle.in","r");
FILE *g=fopen("puzzle.out","w");
char R[255],C[255];
int i,j,N,ne;
int P[100][255];
int cnt[100];
int urm[100];
void rev(int st,int dr)
{
    for(int i=st;i<=(st+dr)/2;i++)
    {
        swap(C[i],C[dr-(i-st)]);
    }
}
void pivotare(int pivot,int nr)
{
    rev(1,nr);
    rev(nr+1,pivot);
    rev(1,pivot);
    if(N!=pivot)
        nr%=(N-pivot);
    else
        nr=0;
    rev(pivot+1,pivot+(N-pivot-nr));
    rev(pivot+(N-pivot-nr)+1,N);
    rev(pivot+1,N);
}
int main()
{
    fgets(R+1,255,f);
    fgets(C+1,255,f);
    N=strlen(R+1)-1;
    for(i=1;i<=N;i++)
    {
        if(C[i]!=R[i])
        {
            for(j=i+1;j<=N&&C[j]!=R[i];j++)
                ;
            ne=j;
            for(j=1;j<ne;j++)
                fprintf(g,"%d ",ne);
            pivotare(ne,ne-1);
            fprintf(g,"%d ",i);
            pivotare(i,1);
        }
        urm[R[i]-'a']++;
    }
    fprintf(g,"0");
    fclose(f);
    fclose(g);
    return 0;
}
