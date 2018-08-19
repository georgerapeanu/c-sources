#include <cstdio>
#include <cmath>
using namespace std;
typedef struct {double x,y;} point;
point P[105];
int N;
double R,rez;
int main()
{
    scanf("%d%lf",&N,&R);
    for(int i=1;i<=N;i++)
        scanf("%lf%lf",&P[i].x,&P[i].y);
    P[N+1]=P[1];
    for(int i=1;i<=N;i++)
    {
        rez+=sqrt(pow(P[i].x-P[i+1].x,2)+pow(P[i].y-P[i+1].y,2));
    }
    rez+=acos(-1)*R*2;
    printf("%.2f",rez);
    return 0;
}
