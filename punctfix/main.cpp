#include <cstdio>
#include <map>
using namespace std;
FILE *f=fopen("punctfix.in","r");
FILE *g=fopen("punctfix.out","w");
map <int,int> M;
int val,i,N;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        M[i-val]++;
    }
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        fprintf(g,"%d\n",M[val]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
