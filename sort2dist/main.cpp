#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f=fopen("sort2dist.in","r");
FILE *g=fopen("sort2dist.out","w");
int N,i,d,st,dr,j,ust;
pair<int,int> A[12505];
char c[1005][35],m[35];
int cmp(char c1[],char c2[])
{
    int a,b;
    a=strlen(c1);
    b=strlen(c2);
    if(a<b)
        return -1;
    if(b<a)
        return 1;
    return strcmp(c1,c2);
}
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {
        fgets(c[i],35,f);
    }
    for(i=N;i>1;i--)
    {
        strcpy(m,c[i]);
        st=i;
        for(j=i-1;j>0;j--)
        {
            if(cmp(m,c[j])==-1)
            {
                strcpy(m,c[j]);
                st=j;
            }
        }
        d=i-st;
        while(d)
        {
            dr=st+((d^(d-1))&d);
            d-=((d^(d-1))&d);
            if(ust<=st)
            A[++A[0].first]=make_pair(st,dr);
            else
            A[++A[0].first]=make_pair(dr,st);
            swap(c[st],c[dr]);
            st=dr;
        }
        ust=dr;
    }
    fprintf(g,"%d\n",A[0].first);
    for(i=1;i<=A[0].first;i++)
    {
        fprintf(g,"%d %d\n",A[i].first,A[i].second);
    }
    fclose(f);
    fclose(g);
    return 0;
}