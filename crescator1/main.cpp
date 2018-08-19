#include <cstdio>
using namespace std;
FILE *f=fopen("crescator1.in","r");
FILE *g=fopen("crescator1.out","w");
int ind;
long long elem,nr;
int A[100005];
int N;
int sumcf(long long a)
{
    int sum=0;
    while(a)
    {
        sum+=a%10;
        a/=10;
    }
    return sum;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&A[i]);
    elem=A[1];
    ind=1;
    while(ind<=N)
    {
        while(ind<=N&&A[ind]<elem)
            ind++;
        if(N<ind)
            break;
        while(A[ind]==elem)
            {nr++;ind++;}
        elem+=sumcf(elem);
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
