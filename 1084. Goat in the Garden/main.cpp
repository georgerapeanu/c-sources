#include <cmath>
#include <cstdio>
#include <cmath>
#define PI 3.141592654
using namespace std;
double L,R;
double unghi,arie;
int main()
{
    scanf("%lf%lf",&L,&R);
    if(R<=L/2)
    {
        printf("%.3f",PI*R*R);
    }
    else if(R>=sqrt(2)*L/2)
        printf("%.3f",L*L);
    else
    {
        L/=2;
        unghi=2*asin(sqrt((R-L)*(R+L))/R);
        arie=R*R*(unghi-sin(unghi))/2;
        printf("%.3f",R*R*PI-4*arie);
    }
    return 0;
}
