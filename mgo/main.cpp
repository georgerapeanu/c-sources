#include <cstdio>
using namespace std;
FILE *f=fopen("mgo.in","r");
FILE *g=fopen("mgo.out","w");
int N,P,i,x,j;
short V[150];
bool nra[150],nrb[150];
int main()
{
    fscanf(f,"%d %d",&P,&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&x);
        if(i%2)
        for(j=x;j<=P&&!nra[j];j++)
            nra[j]=1;
        else
            for(j=x;j<=P&&!nrb[j];j++)
            nrb[j]=1;

    }
    return 0;
}
