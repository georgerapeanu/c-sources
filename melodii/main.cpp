#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("melodii.in","r");
FILE *g=fopen("melodii.out","w");
int N;
int R;
int x,y,z;
long long nr;
vector<int>  baga;
int main()
{
    fscanf(f,"%d %d",&N,&R);
    x=1;y=2;
    baga.push_back(1);
    baga.push_back(2);
    for(int i=3;(x+y)%R!=1||(x+2*y)%R!=2;i++)
    {
        z=(x+y)%R;
        x=y;
        y=z;
        baga.push_back(z);
        nr+=(!z);
    }
    while(N--)
    {
        fscanf(f,"%lld",&nr);
        fprintf(g,"%d\n",baga[(nr-1)%baga.size()]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
