#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("nrcuv.in","r");
FILE *g=fopen("nrcuv.out","w");
char c[300];
int i,n,nr;
int main()
{
    c[0]=' ';
    fgets(c+1,300,f);
    n=strlen(c);
    for(i=1;i<n;i++)
    {
        if(((('a'<=c[i]&&c[i]<='z')||('A'<=c[i]&&c[i]<='Z'))||(c[i]=='-'&&(('a'<=c[i+1]&&c[i+1]<='z')||('A'<=c[i+1]&&c[i+1]<='Z'))))&&(c[i-1]==' '||c[i-1]=='.'||c[i-1]=='?'||c[i-1]=='!'))
        nr++;
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
