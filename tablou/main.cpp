#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("tablou.in","r");
FILE *g=fopen("tablou.out","w");
int L[20005];
int C[20005];
int N,K;
char c;
int val;
int rez;
int p;
int main()
{
    fscanf(f,"%d",&p);
    if(p==1)
    {
        fscanf(f,"%d %d\n",&N,&K);
        for(int i=1;i<=K;i++)
        {
            fscanf(f,"%c %d\n",&c,&val);
            if(c=='L')
                L[val]++;
            else
                C[val]++;
        }
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                rez+=(((L[i]+C[j])&1)==0);
        fprintf(g,"%d",rez);
    }
    else
    {
        fscanf(f,"%d %d",&N,&K);
        rez=(1<<30);
        for(int nrl=1;nrl<=N;nrl++)
        {
            if(N-2*nrl==0)
            {
                if(K==nrl*N)
                {
                    rez=min(nrl,rez);
                }
            }
            else
            {
                if((K-nrl*N)%(N-2*nrl)==0)
                {
                    int nrc=(K-nrl*N)/(N-2*nrl);
                    if(nrc>=0&&nrc<=N)
                        rez=min(rez,nrl+nrc);
                }
            }
        }
        if(rez!=(1<<30))
            fprintf(g,"%d",rez);
        else
            fprintf(g,"0");
    }
    fclose(f);
    fclose(g);
    return 0;
}

