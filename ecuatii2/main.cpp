#include <cstdio>
#include <cctype>
#include <algorithm>
#define x first
#define y second
using namespace std;
FILE *f=fopen("ecuatii2.in","r");
FILE *g=fopen("ecuatii2.out","w");
char C[260];
int coef(int &poz)
{
    if(C[poz]=='x')
        return 1;
    int coef=0;
    while(isdigit(C[poz]))
        coef=coef*10+C[poz]-'0',poz++;
    return coef;
}
pair<int,int> gexpr(int &poz)
{
    int sgn=1;
    int a1=0,a2=0;
    do
    {
        if(C[poz]=='-')
            sgn=-1;
        else
            sgn=1;
        poz++;
        int co=coef(poz);
        if(C[poz]=='x')
            a1+=co*sgn,poz++;
        else
            a2+=co*sgn;
    }
    while(C[poz]=='+'||C[poz]=='-');
    return make_pair(a1,a2);
}
int N;
int main()
{
    fscanf(f,"%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        fgets(C+1,260,f);
        pair<int,int> e1,e2;
        int poz=0;
        e1=gexpr(poz);
        e2=gexpr(poz);
        if(e1.x==e2.x&&e1.y==e2.y) fputs("infinit\n",g);
        else if(e1.x==e2.x&&e1.y!=e2.y) fputs("imposibil\n",g);
        else    fprintf(g,"%.7f\n",1.0*(e1.y-e2.y)/(e2.x-e1.x));
    }
    fclose(f);
    fclose(g);
    return 0;
}
