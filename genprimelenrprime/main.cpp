#include <cstdio>
using namespace std;
FILE *f=fopen("input.in","r");
FILE *g=fopen("output.out","w");
int N,i,j;
bool ciur[2000];
int main()
{
    fscanf(f,"%d",&N);
    ciur[0]=ciur[1]=1;
    for(i=1;i<=N;i++)
        if(!ciur[i])
        for(j=i*i;j<=N;j+=i)
            ciur[j]=1;
    for(i=1;i<=N;i++)
        if(!ciur[i])
            fprintf(g,"%d,",i);
    fclose(f);
    fclose(g);
    return 0;
}
