#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("cifre.in","r");
FILE *g=fopen("cifre.out","w");
int N,frecv[10],i,nr,cf,j;
long long S;
int rez[100005],C[100];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&nr);
        if(nr==0)
            frecv[0]++;
        cf=0;
        while(nr)
        {
            frecv[nr%10]++;
            nr/=10;
            cf++;
        }
        C[cf]++;
    }
    i=1;j=0;
    while(frecv[j]==0)
        j++;
    while(C[i]--)
    {
        rez[++rez[0]]=j;
        frecv[0]--;
        while(frecv[j]==0)
            j++;
    }
    p10=10;
    fclose(f);
    fclose(g);
    return 0;
}
