#include <cstdio>
using namespace std;
FILE *f=fopen("monezi2.in","r");
FILE *g=fopen("monezi2.out","w");
bool B[101005];
int N,Q,val,V;
int main()
{
    fscanf(f,"%d",&N);
    B[0]=1;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        V+=val;
        for(int j=0;j<=100000-V;j++)
            if(B[j])
                B[j+V]=1;
    }
    fscanf(f,"%d",&Q);
    for(int i=1;i<=Q;i++)
    {
        fscanf(f,"%d",&val);
        if(B[val])
            fprintf(g,"DA\n");
        else
            fprintf(g,"NU\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
