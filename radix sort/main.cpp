#include <cstdio>
#include <cstring>
#define PW 10
#define MK ((1<<PW)-1)
using namespace std;
FILE *f=fopen("radixsort.in","r");
FILE *g=fopen("radixsort.out","w");
int cnt[MK+2];
int V[10000005];
int VN[10000005];
int N,A,B,C;
int main()
{
    fscanf(f,"%d%d%d%d",&N,&A,&B,&C);
    V[1]=B;
    for(int i=2;i<=N;i++)
    {
        V[i]=(1LL*A*V[i-1]+B)%C;
    }
    for(int sh=0;sh<32;sh+=PW)
    {
        for(int i=1;i<=N;i++)
        {
            cnt[((V[i]>>sh)&MK)+1]++;
        }
        cnt[0]=1;
        for(int i=1;i<=MK;i++)
            cnt[i]+=cnt[i-1];
        for(int i=1;i<=N;i++)
        {
            VN[cnt[(V[i]>>sh)&MK]++]=V[i];
        }
        memcpy(V,VN,sizeof(VN));
        memset(cnt,0,sizeof(cnt));
    }
    for(int i=1;i<=N;i+=10)
        fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
