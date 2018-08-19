#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f=fopen("antic.in","r");
FILE *g=fopen("antic.out","w");
map <char,int> ord;
char S[30],c[205],d[205];
char V[1005][105];
int N,i,l,ind[1005];
bool ok;
int cmp(char a[],char b[])
{
    l=0;
    int A=strlen(a);
    int B=strlen(b);
    while(a[l]==b[l]&&l<=A&&l<=B)
        l++;
    if(l<=A&&l<=B)
        return ord[a[l]]<ord[b[l]] ? -1:1;
    return 0;
}
int tmpcmp(char a[],char b[])
{
    memset(c,'\0',201);
    memset(d,'\0',201);
    strcpy(c,a);strcat(c,b);
    strcpy(d,b);strcat(d,a);
    return cmp(c,d);
}
int main()
{
    fgets(S,30,f);
    for(i=0;i<26;i++)
        ord[S[i]]=i;
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
        {fscanf(f,"%s\n",V[i]);ind[i]=i;}
    do
    {
        ok=0;
        for(i=1;i<N;i++)
        {
            if(tmpcmp(V[i],V[i+1])==-1||(tmpcmp(V[i],V[i+1])==0&&ind[i]<ind[i+1]))
                {swap(V[i],V[i+1]);swap(ind[i],ind[i+1]);ok=1;}
        }
    }
    while(ok==1);
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",ind[i]);
    fclose(f);
    fclose(g);
    return 0;
}
