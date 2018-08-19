#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;
FILE *f=fopen("sortare2.in","r");
FILE *g=fopen("sortare2.out","w");
bitset<100001> B;
int N;
int elem;
int nr;
int main()
{
    fscanf(f,"%d",&N);
    B[0]=1;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&elem);
        if(B[elem-1])
        {
            B[elem-1]=0;
            B[elem]=1;
        }
        else
        {
            nr++;
            B[elem]=1;
        }
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
