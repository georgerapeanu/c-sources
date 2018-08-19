#include <cstdio>
using namespace std;
FILE *f, *g;
char vec[40];
int n;
void back(int nrd,int nri)
{
    if(nrd!=n||nri!=n)
    {
        vec[nrd+nri]='(';
        if(nrd+1<=n)
        back(nrd+1,nri);
        vec[nrd+nri]=')';
        if(nrd>=nri+1&&nri+1<=n)
        back(nrd,nri+1);
    }
    if(nrd==n&&nri==n)
    {
         fprintf(g,"%s\n",vec);
    }
}
int main()
{
    f=fopen("paranteze.in","r");
    g=fopen("paranteze.out","w");
    fscanf(f,"%d",&n);
    back(0,0);
    return 0;
}
