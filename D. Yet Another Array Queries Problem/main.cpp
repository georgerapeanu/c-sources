#include <cstdio>
using namespace std;
int N,Q,M;
int A[200005];
int B[105];
struct data{int t,x,y;};
data q[200005];
int main()
{
    scanf("%d %d %d",&N,&Q,&M);
    for(int i=1;i<=N;i++)scanf("%d",&A[i]);
    for(int i=1;i<=Q;i++)scanf("%d%d%d",&q[i].t,&q[i].x,&q[i].y);
    for(int i=1;i<=M;i++)scanf("%d",&B[i]);
    for(int i=1;i<=M;i++)
    {
        int poz=B[i];
        for(int j=Q;j;j--)
        {
            if(q[j].x<=poz&&poz<=q[j].y)
            {
                if(q[j].t==1){if(poz==q[j].x)poz=q[j].y;else poz=poz-1;}
                else    poz=q[j].y-poz+q[j].x;
            }
        }
        printf("%d ",A[poz]);
    }
    return 0;
}
