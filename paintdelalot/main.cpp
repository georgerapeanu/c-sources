#include <cstdio>
using namespace std;
FILE *f=fopen("paint.in","r");
FILE *g=fopen("paint.out","w");
int V[250005];
int d,l;
int nr,N,i,cnt,M,K;
int main()
{
    fscanf(f,"%d %d %d",&N,&K,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&d,&l);
        V[d]++;
        V[d+l]--;
    }
    for(i=0;i<N;i++)
    {
        cnt+=V[i];
        if(cnt<K)
            nr++;
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
