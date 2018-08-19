#include <cstdio>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#define x first
#define y second
using namespace std;
FILE *f=fopen("puncte.in","r");
FILE *g=fopen("puncte.out","w");
unordered_map<int,int> fx,fy;
int N,a,b;
typedef pair<int,int> point;
point V[250005];
int urm[250005];
int nr1,nr2;
bool O;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].x,&V[i].y);
        fx[V[i].x]++;
        fy[V[i].y]++;
        a=max(a,max(fx[V[i].x],fy[V[i].y]));
        if(!V[i].x&&!V[i].y)
            O=1;
        if(V[i].x==V[i].y)
            nr1++;
        if(V[i].x==-V[i].y)
            nr2++;
        urm[i]=i%N+1;
    }
    fprintf(g,"%d\n",a);
    b=(nr1>=2)+(nr2>=2);
    if(O)
    {
        nr1--;
        nr2--;
    }
    b+=nr1*nr2;
    fprintf(g,"%d\n",b);
    sort(V+1,V+1+N);
    int i=1,prev=N;
    for(;urm[i]!=i;prev=urm[urm[i]],i=urm[urm[urm[i]]])
    {
        urm[prev]=urm[i];
    }
    fprintf(g,"%d",V[i].x);
    fclose(f);
    fclose(g);
    return 0;
}
