#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("ordonare.in","r");
FILE *g=fopen("ordonare.out","w");
int  prior[30];
int i,N,lin,col,j;
bool ok;
char c[2050],m[1005][35],tmp[35];
bool comp(char a[],char b[])
{
    int i=0;
    while(a[i]==b[i]&&a[i]!='\0')
        i++;
    if(a[i]==b[i])
        return 1;
    if(a[i]=='\0')
        return 0;
    if(b[i]=='\0')
        return 1;
    if(prior[a[i]-'a']<prior[b[i]-'a'])
        return 0;
    return 1;
}

void qsort(int st,int dr)
{
    int i=st;
    int j=dr;
    char pivot[35];
    strcpy(pivot,m[(st+dr)/2]);
    while(i<=j)
    {
        while(comp(m[i],pivot)==0)
            i++;
        while(comp(pivot,m[j])==0)
            j--;
        if(i<=j)
        {
            swap(m[i],m[j]);
            i++;
            j--;
        }
    }
    if(i<dr)
        qsort(i,dr);
    if(j>st)
        qsort(st,j);
}
int main()
{
    fgets(c,2050,f);
    N=strlen(c);
    for(i=0;i<N-1;i++)
    {
        prior[c[i]-'a']=i;
    }
    fgets(c,2050,f);
    i=0;
    lin=1;col=0;
    while(c[i]!='\n')
    {
        while(c[i]=='.'||c[i]==' '||c[i]==','||c[i]==';'||c[i]=='!'||c[i]=='?'||c[i]==':')
            i++;
        if(c[i]!='\n')
        {
            while('a'<=c[i]&&c[i]<='z')
            {
                m[lin][col++]=c[i];
                i++;
            }
            lin++;
            col=0;
        }
    }
    qsort(1,lin-1);
    for(i=1;i<lin;i++)
        fprintf(g,"%s ",m[i]);
    fprintf(g,"\n");
    fclose(f);
    fclose(g);
    return 0;
}
