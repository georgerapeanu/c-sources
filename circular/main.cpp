#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("circular.in","r");
FILE *g=fopen("circular.out","w");
int N,i;
char C[20005];
char A[20005];
void p()
{
    char c=C[N-1];
    for(int i=N-1;i>0;i--)
        C[i]=C[i-1];
    C[0]=c;
}
int main()
{
    fscanf(f,"%d\n",&N);
    fgets(A,20005,f);
    fgets(C,20005,f);
    for(i=1;i<=N;i++)
    {
        if(strcmp(A,C)==0)
        {
            fprintf(g,"%d",i-1);
            return 0;
        }
        p();
    }
    fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
