#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("dale.in","r");
FILE *g=fopen("dale.out","w");
int N,i,j,l;
vector <short> V;
int main()
{
    fscanf(f,"%d",&N);
    V.push_back(0);
    V.push_back(1);
    l=1;
    for(i=1;i<=N+1;i++)
    {
        for(j=l;j>=1;j--)
            V[j]*=2;
        for(j=l;j>=2;j--)
        {
                V[j-1]+=V[j]/10;
                V[j]%=10;
        }
        if(V[1]>9)
        {
            l++;
            V[0]=V[1]/10;
            V[1]%=10;
            V.insert(V.begin(),0);
        }
    }
    for(i=1;i<=l;i++)
        fprintf(g,"%hd",V[i]);
    fprintf(g,"\0");
    fclose(f);
    fclose(g);
    return 0;
}
