#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("dicsi.in","r");
FILE *g=fopen("dicsi.out","w");
int N;
int col[100005];
int nrcul;
int main()
{
    fscanf(f,"%d",&N);
    col[1]=1;
    for(int i=1;i<=N;i++)
    {
        for(int j=i*2;j<=N;j+=i)
            col[j]=max(col[j],col[i]+1);
        nrcul=max(nrcul,col[i]);
    }
    fprintf(g,"%d\n",nrcul);
    for(int i=1;i<=N;i++)
        fprintf(g,"%d ",col[i]);
    fclose(f);
    fclose(g);
    return 0;
}
