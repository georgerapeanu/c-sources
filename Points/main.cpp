#include <cstdio>
#include <fstream>
#define x first
#define y second
using namespace std;
FILE *f=fopen("points.in","r");
FILE *g=fopen("points.out","w");
int N;
pair<int,int> V;
long long fr[4];
long long rez;
bool rest(int r1,int r2,int r3,int r4,int r5,int r6)
{
    int tmp=r1*r4+r3*r6+r5*r2-r1*r6-r3*r2-r5*r4;
    if(tmp%2==0)
        return 0;
    return 1;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d",&V.x,&V.y);
        fr[((V.x&1)<<1)+(V.y&1)]++;
    }
    for(int r1=0;r1<2;r1++)
    {
        for(int r2=0;r2<2;r2++)
        {
            for(int r3=0;r3<2;r3++)
            {
                for(int r4=0;r4<2;r4++)
                {
                    for(int r5=0;r5<2;r5++)
                    {
                        for(int r6=0;r6<2;r6++)
                        {
                            if(rest(r1,r2,r3,r4,r5,r6)==0)
                            {
                                rez+=fr[r1*2+r2]*(fr[r3*2+r4]-(r1==r3&&r2==r4))*(fr[r5*2+r6]-(r1==r5&&r2==r6)-(r3==r5&&r4==r6));
                            }
                        }
                    }
                }
            }
        }
    }
    fprintf(g,"%lld",rez/6);
    return 0;
}
