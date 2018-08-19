#include <cstdio>
#include <deque>
using namespace std;
FILE *f=fopen("carti3.in","r");
FILE *g=fopen("carti3.out","w");
deque <int> D;
int i,N,M,sens,X,C,a,b;
int main()
{
    fscanf(f,"%d %d",&N,&C);
    sens=1;
    for(i=1;i<=C;i++)
    {
        fscanf(f,"%d",&X);
        D.push_back(X);
    }
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&X);
        if(X==-1)
            sens*=-1;
        else
        {
            if(sens==1)
                D.push_front(X);
            else
                D.push_back(X);
        }
        a=D.front();
        b=D.back();
    }
    if(sens==-1)
    {
        while(!D.empty())
        {
            X=D.back();
            D.pop_back();
            fprintf(g,"%d\n",X);
        }
    }
    else
    {
        while(!D.empty())
        {
            X=D.front();
            D.pop_front();
            fprintf(g,"%d\n",X);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
