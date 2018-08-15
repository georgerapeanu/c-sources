#include <cstdio>
using namespace std;
FILE *f=fopen("vecini.in","r");
FILE *g=fopen("vecini.out","w");
int N;
int lg[100005];
void printans(int N)
{
    if(N==1)
    {
        fprintf(g,"1 ");
        return ;
    }
    int tmp=N-(1<<lg[N-1]);
    printans(tmp);
    for(int i=1;i<=N-2*tmp;i++)
        fprintf(g,"0 ");
    printans(tmp);
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=2;i<=N;i++)
        lg[i]=1+lg[i/2];
    printans(N);
    fclose(f);
    fclose(g);
    return 0;
}
