#include <cstdio>
using namespace std;
int sol=0;
bool ok(int h,int m)
{
    return (h/10==m%10&&h%10==m/10);
}
void up(int &h,int &m)
{
    sol++;
    m++;
    if(m==60){h++;m=0;}
    if(h==24)h=0;
}
int h,m;
int main()
{
    scanf("%d:%d",&h,&m);
    while(!ok(h,m))up(h,m);
    printf("%d",sol);
    return 0;
}
