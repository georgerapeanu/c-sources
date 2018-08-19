#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f=fopen("fences.in","r");
FILE *g=fopen("fences.out","w");
int fr[280];
char C[200005];
int T;
int main()
{
    fscanf(f,"%d\n",&T);
    while(T--)
    {
        fgets(C+1,200005,f);
        int N=strlen(C+1);N-=(C[N]=='\n');
        for(int i=1;i<=N;i++)
        {
            fr[C[i]]++;
        }
        fprintf(g,"%lld\n",(1LL*min(fr['R'],fr['L'])*min(fr['U'],fr['D'])));
        fr['R']=fr['D']=fr['L']=fr['U']=0;
    }
    fclose(f);
    fclose(g);
    return 0;
}
