#include <cstdio>
using namespace std;
FILE *f=fopen("bitone.in","r");
FILE *g=fopen("bitone.out","w");
int J[1000005];
long long V,fV;
int S[1000005];
int i;
long long st,dr;
long long N,Q;
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V);
        if(i==1)
            S[1]=J[1]=1;
        else
        {
            if(V>fV)
            {
                J[i]=i;
                S[i]=S[i-1];
            }
            else if(V==fV)
            {
                S[i]=S[i-1];
                J[i]=J[i-1];
            }
            else
            {
                S[i]=i;
                J[i]=J[i-1];
            }
        }
        fV=V;
    }
    fscanf(f,"%lld",&Q);
    for(i=1;i<=Q;i++)
    {
        fscanf(f,"%lld %lld",&st,&dr);
        if(S[J[dr]]<=st)
            fputc('1',g);
        else
            fputc('0',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
