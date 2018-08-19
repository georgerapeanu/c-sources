#include <cstdio>
using namespace std;
FILE *f=fopen("mincinosi.in","r");
FILE *g=fopen("mincinosi.out","w");
int frecv[1000005];
int N,i,maxim=-1;
int rez[1000005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&rez[i]);
        frecv[rez[i]]++;
    }
    for(i=0;i<=N;i++)
        if(N-i-frecv[i]==0)
            if(maxim==-1||frecv[i]>frecv[maxim])
                maxim=i;
    fprintf(g,"%d\n",N-maxim);
    for(i=1;i<=N;i++)
        if(rez[i]==maxim)
            fprintf(g,"%d\n",i);
    fclose(f);
    fclose(g);
    return 0;
}
