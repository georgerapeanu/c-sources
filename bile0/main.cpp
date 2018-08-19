#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("bile.in","r");
FILE *g=fopen("bile.out","w");
int N,S,st,dr,last,mid,setat;
long long rez;
int V[50005],i;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        S+=V[i];
    }
    S/=N;
    st=1;
    dr=N;
    while(st<=dr)
    {
        mid=(st+dr)/2;
        if(V[mid]<=S)
        {
            last=mid;
            st=mid+1;
        }
        else
            dr=mid-1;
    }
    if(S-V[last]<=V[last+1]-S)
        setat=last;
    else
        setat=last+1;
    for(i=setat-1;i>0;i--)
    {
        rez+=V[setat]-(setat-i)-V[i];
    }
    for(i=setat+1;i<=N;i++)
    {
        rez+=V[i]-(V[setat]+(i-setat));
    }
    fprintf(g,"%lld",rez);
    return 0;
}
