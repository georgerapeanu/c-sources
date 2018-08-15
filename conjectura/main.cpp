#include <cstdio>
using namespace std;
FILE *f=fopen("conjectura.in","r");
FILE *g=fopen("conjectura.out","w");
int N,i;
char c[20000];
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {
        fgets(c,20000,f);
    }
    return 0;
}
