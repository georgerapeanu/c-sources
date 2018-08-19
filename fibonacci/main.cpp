#include <cstdio>
using namespace std;
FILE *f=fopen("fibonacci.in","r");
FILE *g=fopen("fibonacci.out","w");
int N;
int fib(long nr,int prev,int prev2)
{
    if(nr==N-1)
        return (prev+prev2)%982451653;
    return fib(nr+1,prev2,(prev2+prev)%982451653);
}
int main()
{
    fscanf(f,"%d",&N);
    if(N==1)
        fprintf(g,"0");
    else if(N==2)
        fprintf(g,"1");
    else fprintf(g,"%d",fib(2,1,1));
    fclose(f);
    fclose(g);
    return 0;
}
