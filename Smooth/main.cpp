#include <cstdio>
using namespace std;
FILE *f=fopen("smooth.in","r");
FILE *g=fopen("smooth.out","w");
int N;
long long A,B;
bool ok=1;
long long rez=0;
int val[]={0,2,3,5,7};
int most(long long i)
{
    if(i==1)return 0;
    if(i%2==0)return 1+most(i/2);
    if(i%3==0)return 1+most(i/3);
    if(i%5==0)return 1+most(i/5);
    if(i%7==0)return 1+most(i/7);
}
int least(long long i)
{
    if(i==1)return 0;
    if(i%8==0)return 1+least(i/8);
    if(i%9==0)return 1+least(i/9);
    if(i%4==0)return 1+least(i/4);
    if(i%6==0)return 1+least(i/6);
    if(i%7==0)return 1+least(i/7);
    if(i%5==0)return 1+least(i/5);
    if(i%3==0)return 1+least(i/3);
    if(i%2==0)return 1+least(i/2);
}
void btr(int pas,long long nr)
{
    if(pas>4)
    {
        if(A<=nr&&nr<=B)rez+=most(nr)-least(nr)+(nr!=1);return ;
    }
    for(;;)
    {
        btr(pas+1,nr);
        if(B<val[pas]*nr)return;
        nr*=val[pas];
    }
}
int main()
{
    fscanf(f,"%lld %lld",&A,&B);
    btr(1,1);
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
