#include <cstdio>
#include <map>
using namespace std;
FILE *f=fopen("fsb.in","r");
FILE *g=fopen("fsb.out","w");
int N,V[200005],i,j,nr;
map <int,int> M;
char c;
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
        {
            c=fgetc(f);
            if(c=='0')
                V[i]=V[i-1]-1;
            else
                V[i]=V[i-1]+1;
            if(!V[i])
                nr++;
            nr+=M[V[i]];
            M[V[i]]++;
        }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
