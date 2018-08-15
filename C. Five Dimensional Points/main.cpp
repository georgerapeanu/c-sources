#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
struct punct
{
    int x[6];
};
punct V[1005];
set<punct> S;
int N;
int rez;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=5;j++)scanf("%d",&V[i].x[j]);
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=i+1;j<=N;j++)
        {
            for(int conf=0;conf<(1<<5);conf++)
            {
                punct ceva;
                for(int bit=0;bit<5;bit++)
                {
                    if((conf>>bit)&1)
                    {
                        ceva.x[bit+1]=V[i].x[bit+1];
                    }
                    else
                    {
                        ceva.x[bit+1]=V[j].x[bit+1];
                    }
                }
                S.erase(ceva);
            }
        }
    }
    printf("%d")
    return 0;
}
