#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("noname2.in","r");
FILE *g=fopen("noname2.out","w");
int V[100005];
int N,K,maxim;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&V[i]);
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++) V[i]+=V[i-1];
    int st=0,dr=0;
    for(int i=1;i<=N;i++)
    {
        dr=max(dr,i+1);
        int disp=K-(V[dr-1]-V[i-1]-(dr-i)*(V[i]-V[i-1]));
        while(st<i-1&&disp<(i-st-1)*(V[i]-V[i-1])-V[i-1]+V[st])
            st++;
        disp-=(i-st-1)*(V[i]-V[i-1])-V[i-1]+V[st];
        while(dr<=N&&disp>=V[dr]-V[dr-1]-V[i]+V[i-1])
        {
            disp-=V[dr]-V[dr-1]-V[i]+V[i-1];
            dr++;
        }
        while(st<i-1&&dr<=N&&V[i]-V[i-1]-V[st+1]+V[st]>V[dr]-V[dr-1]-V[i]+V[i-1])
        {
            disp+=(V[i]-V[i-1]-V[st+1]+V[st])-(V[dr-1]-V[dr-2]-V[i]+V[i-1]);
            st++;
            dr++;
        }
        while(dr<=N&&disp>=V[dr]-V[dr-1]-V[i]+V[i-1])
        {
            disp-=V[dr]-V[dr-1]-V[i]+V[i-1];
            dr++;
        }
        maxim=max(maxim,dr-st-1);
    }
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
