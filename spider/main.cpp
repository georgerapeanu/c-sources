#include <cstdio>
using namespace std;
FILE *f,*g;
int x,y,minim=6568,m[81][81],gasite;
void back(int nr,int i, int j)
{
    if(j<x)
    back(nr+1,i,j+1);
    if(i<y)
    back(nr+1,i+1,j);
    if(nr<minim&&(x==j&&y==i))
    {
        minim=nr;
        gasite=1;
    }
    else if(nr==minim&&(x==j&&y==i))
    gasite++;
}
int main()
{
    f=fopen("spider.in","r");
    fscanf(f,"%d %d",&x,&y);
    fclose(f);
    back(0,0,0);
    g=fopen("spider.out","w");
    fprintf(g,"%d",gasite);
    fclose(g);
    return 0;
}
