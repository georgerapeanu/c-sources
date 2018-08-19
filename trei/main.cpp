#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("trei.in","r");
FILE *g=fopen("trei.out","w");
int frecv[3],N,nr,minim,i;
bool e1,e2;
long long V[200005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V[i]);
        frecv[V[i]%3]++;
    }
    if(frecv[1])
        e1=1;
    if(frecv[2])
        e2=1;
    minim=min(frecv[1],frecv[2]);
    frecv[1]-=minim;
    frecv[2]-=minim;
    nr+=2*minim;
    nr+=frecv[0];
    minim=frecv[1]-frecv[1]%3;
    frecv[1]%=3;
    nr+=minim;
    minim=frecv[2]-frecv[2]%3;
    nr+=minim;
    frecv[2]%=3;
    i=1;
    if(frecv[1]==2&&e2)
        {frecv[2]=1;frecv[1]=0;nr++;}
    if(frecv[2]==2&&e1)
        {frecv[1]=1;frecv[2]=0;nr++;}
    fprintf(g,"%d\n",nr);
    while(frecv[1]||frecv[2])
    {
        minim=V[i]%3;
        if(frecv[minim]&&minim!=0)
        {
            fprintf(g,"%lld ",V[i]);
            frecv[minim]--;
        }
        i++;
    }
    fclose(f);
    fclose(g);
    return 0;
}
