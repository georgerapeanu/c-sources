#include <cstdio>
using namespace std;
FILE *f=fopen("ciurulet.in","r");
FILE *g=fopen("ciurulet.out","w");
int N;
char C[1000005];
char rez[1000005];
int nr;
int main()
{
    fscanf(f,"%d\n",&N);
    fgets(C+2,1000005,f);
    N--;
    for(int i=2;i<=N+1;i++)
    {
        if(rez[i]!='\0')continue;
        if(C[i]=='0'){rez[i]='0';continue;}
        bool all0=1;
        for(int j=i+i;j<=N+1&&all0;j+=i)
        {
            all0&=(C[j]=='0'||C[j]=='?');
        }
        if(all0)
        {
            for(int j=i;j<=N+1;j+=i)
            {
                nr+=(rez[j]!='1');
                rez[j]='1';
            }
        }
        else
        {
            rez[i]='0';
        }
    }
    fprintf(g,"%d\n%s",nr,rez+2);
    fclose(f);
    fclose(g);
    return 0;
}
