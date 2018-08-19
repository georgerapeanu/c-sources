#include <cstdio>
#include <algorithm>
using namespace std;
int N;
int K;
int val;
int sum;
int rez=0;
FILE *f=fopen("perle2.in","r");
FILE *g=fopen("perle2.out","w");
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        val-=K;
        sum=max(val,sum+val);
        rez=max(rez,sum);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
