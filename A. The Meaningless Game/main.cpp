#include <cstdio>
#include <cmath>
using namespace std;
int a,b;
int T;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&a,&b);
        if(1LL*a*a==b||1LL*b*b==a){printf("YES\n");continue;}
        long long prod=1LL*a*b;
        prod=pow(prod,(long double)1/3);
        if(a%prod==0&&b%prod==0&&prod*prod*prod==1LL*a*b){printf("YES\n");continue;}prod--;
        if(prod&&a%prod==0&&b%prod==0&&prod*prod*prod==1LL*a*b){printf("YES\n");continue;}prod+=2;
        if(a%prod==0&&b%prod==0&&prod*prod*prod==1LL*a*b){printf("YES\n");continue;}
        printf("NO\n");
    }
    return 0;
}
