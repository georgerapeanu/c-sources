#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("banda10.in","r");
FILE *g=fopen("banda10.out","w");
long long  N,i,M=1,j,l;
char c[1010];
vector <short> V;
vector <short> rez;
int main()
{
    fscanf(f,"%lld\n",&N);
    fgets(c+1,1010,f);
    fclose(f);
    V.push_back(0);
    V.push_back(1);
    rez.push_back(0);
    for(i=1;i<=N;i++)
    {
        if(c[N-i+1]=='1')
        {
                while(l<M)
                {
                 rez.insert(rez.begin(),0);
                 l++;
                }
                for(j=1;j<=M;j++)
                {
                    rez[j]+=V[j];
                }
                 for(j=l;j>=2;j--)
                {
                rez[j-1]+=rez[j]/10;
                rez[j]%=10;
                }
                if(rez[1]>9)
                {
                M++;
                rez[0]=rez[1]/10;
                rez[1]%=10;
                rez.insert(rez.begin(),0);
                }
        }
        for(j=M;j>=1;j--)
            V[j]*=2;
        for(j=M;j>=2;j--)
        {
                V[j-1]+=V[j]/10;
                V[j]%=10;
        }
        if(V[1]>9)
        {
            M++;
            V[0]=V[1]/10;
            V[1]%=10;
            V.insert(V.begin(),0);
        }
    }
    fprintf(g,"%lld",l);
    fclose(g);
    return 0;
}