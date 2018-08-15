#include <cstdio>
#include <forward_list>
using namespace std;
FILE *f=fopen("grid.in","r");
FILE *g=fopen("grid.out","w");
forward_list<int> A[3];
int N,K;
int X1,X2,Y1,Y2;
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int k=0;k<3;k++)
        for(int i=N;i;i--)
            A[k].insert_after(A[k].before_begin(),N*k+i);
    for(int i=1;i<=K;i++)
    {
        fscanf(f,"%d%d%d%d",&X1,&Y1,&X2,&Y2);
        forward_list<int>::iterator it1,it2,it;
        it1=A[X1].begin();if(Y1>0) advance(it1,Y1-1);else it1=A[X1].before_begin();
        it=A[X1].begin();advance(it,Y1);
        int val=*it;A[X1].erase_after(it1);
        it2=A[X2].begin();if(Y2>0) advance(it2,Y2-1); else it2=A[X2].before_begin();
        A[X2].insert_after(it2,val);
    }
    for(int i=0;i<3;i++,fputc('\n',g))
        for(auto it:A[i])
            fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
