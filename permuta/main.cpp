#include <cstdio>
#include <deque>
using namespace std;
FILE *f=fopen("permuta.in","r");
FILE *g=fopen("permuta.out","w");
deque<int> D;
int X[100005],i,N,tmp;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&X[i]);
    }
    for(i=N;i>=1;i--)
    {
        if(i==N)
            D.push_back(X[i]);
        else
        {
            tmp=D.back();
            D.pop_back();
            D.push_front(tmp);
            D.push_front(X[i]);
        }
    }
    while(!D.empty())
    {
        tmp=D.front();
        D.pop_front();
        fprintf(g,"%d ",tmp);
    }
    fclose(f);
    fclose(g);
    return 0;
}
