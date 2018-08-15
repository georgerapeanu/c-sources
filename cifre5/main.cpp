#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("cifre5.in","r");
FILE *g=fopen("cifre5.out","w");
char N[25];
int cost[10]={6,2,5,5,4,5,6,3,7,6};
int cer,len,a;
unsigned long long b;
int V[]={1,5,1,2,2,3,1,2,0,0};
int VV[]={1,6,1,2,2,3,1,4,0,1};
int main()
{
    fscanf(f,"%d\n",&cer);
    fgets(N+1,25,f);
    len=strlen(N+1);
    len=len-(N[len]=='\n');
    if(cer==1)
    {
        for(int i=1;i<=len;i++)
            a+=cost[N[i]-'0'];
        fprintf(g,"%d",a);
    }
    else
    {
        unsigned long long cfdupa=1;
        for(int i=len;i>0;i--)
        {
            b=b+cfdupa*V[N[i]-'0'];
            cfdupa*=(VV[N[i]-'0']+1);
        }
        fprintf(g,"%llu",b);
    }
    fclose(f);
    fclose(g);
    return 0;
}
