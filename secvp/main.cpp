#include <cstdio>
using namespace std;
FILE *f=fopen("secvp.in","r");
FILE *g=fopen("secvp.out","w");
bool E[1000005];
int N,K,V[100000];
int P[80000];
long long i;
long long j,suma,T;
int X,st,dr,mij,last,minK=999999999,nrs;
int main()
{
    E[0]=E[1]=1;
    for(i=2;i<=1000000;i++)
        if(!E[i])
        {
            for(j=i*i;j<=1000000;j+=i)
                E[j]=1;
            P[++P[0]]=i;
        }
    P[++P[0]]=1000003;
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&X);
        if(X>=2)
        {st=1;
        dr=78499;
        while(st<=dr)
        {
            mij=(st+dr)/2;
            if(P[mij]>X)
                dr=mij-1;
            else
            {
                last=mij;
                st=mij+1;
            }
        }
        if(X-P[last]<P[last+1]-X)
            V[i]=X-P[last];
        else
            V[i]=P[last+1]-X;
        }
        else
            V[i]=2-X;
        if(i<K)
            suma+=V[i];
        else
        {
               suma+=V[i];
            suma-=V[i-K];
            if(suma<minK)
            {
                minK=suma;
                nrs=1;
            }
            else if(suma==minK)
            {
                nrs++;
            }
        }
        T+=V[i];
    }
    fprintf(g,"%d\n",T);
    fprintf(g,"%d %d",minK,nrs);
    fclose(f);
    fclose(g);
    return 0;
}
