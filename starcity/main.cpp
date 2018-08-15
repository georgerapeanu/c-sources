#include <cstdio>
#include <queue>
using namespace std;
FILE *g=fopen("starcity.out","w");
FILE *f=fopen("starcity.in","r");
int N;
rez(int config[])
{
    i=2;
    while(config[i]!=N-1)
        i++;
    lib=i;
    for(i=1;i<N;i++)
    {
        if(config[i]!=i)
        {
            if(config[N-1]!=N-1)
            {
                j=config[i];
                mutari[++mutari[0].first]=make_pair(1,i);
                mutari[++mutari[0].first]=make_pair(1,lib);
                swap(config[i],config[lib]);
                lib=i;
                while(j!=i)
                {

                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%d",&N);

    fclose(f);
    fclose(g);
    return 0;
}
