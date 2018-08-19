#include <cstdio>
using namespace std;
FILE *f=fopen("psychtraining.in","r");
FILE *g=fopen("psychtraining.out","w");
int nrpasi;
int N;
int st,dr;
char C[505];
int main()
{
    fscanf(f,"%d",&N);
    while((1<<nrpasi)<N)nrpasi++;
    fprintf(g,"%d\n",nrpasi);
    for(int i=1;i<=N;i++) C[i]='a';
    for(;nrpasi;nrpasi--)
    {
        st=dr=1;
        for(int i=2;i<=N+1;i++)
        {
            if(C[i]==C[dr])
                dr++;
            else
            {
                for(int j=st;j<=(st+dr)/2;j++)
                {
                    C[j]='a';
                }
                for(int j=(st+dr)/2+1;j<=dr;j++)
                {
                    C[j]='b';
                }
                st=dr=i;
            }
        }
        fputs(C+1,g);
        fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
