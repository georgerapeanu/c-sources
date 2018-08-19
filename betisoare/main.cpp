#include <fstream>
using namespace std;
ifstream f("betisoare.in");
ofstream g("betisoare.out");
long nr[1000000],i,j,s,k,l,n,cj;
char c;
bool o[1000000];
int main()
{
    f>>n;c=f.get();
    for(l=1;l<=n;l++)
    {
        for(i=0;i<=cj+1;i++)
        {
           nr[i]=o[i]=0;
        }
        s=0;
        i=0;j=0;
    do
    {
        c=f.get();
        if(c=='I')
        {
            nr[i]++;
        }
        if(c=='*')
        {
          o[j]=1;i++;j++;
        }
        if(c=='+')
        {
            o[j]=0;i++;j++;
        }
    }
    while(c!='\n');
        cj=j;
     for(i=0;i<j;i++)
     {
         if(o[i]==1)
         {
             nr[i]=nr[i]*nr[i+1];
             for(k=i+1;k<j;k++)
             {
                   nr[k]=nr[k+1];o[k-1]=o[k];
             }
             j--;i--;
         }
     }
     for(i=0;i<=j;i++)
     s=s+nr[i];
     g<<s<<'\n';
    }
     f.close();g.close();
    return 0;
}
