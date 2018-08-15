#include <cstdio>
using namespace std;
FILE *f=fopen("hanoi.in","r");
FILE *g=fopen("hanoi.out","w");
int N;
void hanoi(int n,int a,int b,int c)
{
    if(n>0)
    {
        hanoi(n-1,a,c,b);
        fprintf(g,"%d %d %d\n",n,a,b);
        hanoi(n-1,c,b,a);
    }
}
int main()
{
    fscanf(f,"%d",&N);
    hanoi(N,1,2,3);
    fclose(f);
    fclose(g);
    return 0;
}
