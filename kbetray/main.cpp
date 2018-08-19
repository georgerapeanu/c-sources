#include <cstdio>
#include <algorithm>
#define nmax 100005
using namespace std;
FILE *f=fopen("kbetray.in","r");
FILE *g=fopen("kbetray.out","w");
int N,K,i,maxim[nmax],minim[nmax],A,B;
long long rez;
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(i=1;i<=N;i++)
        {
            fscanf(f,"%d%d",&A,&B);
            if(A>B)
                {
                    maxim[i]=A;
                    minim[i]=B;
                }
            else
                {
                    maxim[i]=B;
                    minim[i]=A;
                }
            rez+=maxim[i];
        }
    sort(maxim,maxim+N+1);
    sort(minim,minim+N+1);
    for(i=1;i<=K&&minim[N-i+1]-maxim[i]>0;i++)
        rez+=minim[N-i+1]-maxim[i];
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
