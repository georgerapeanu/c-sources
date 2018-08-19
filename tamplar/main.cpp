#include <cstdio>
#include <vector>
#define BASE 1000
using namespace std;
FILE *f=fopen("tamplar.in","r");
FILE *g=fopen("tamplar.out","w");
int L;
vector <int> rez;
void mul(vector<int> &a,int nr)
{
    int t=0,n=a.size();
    for(int i=0;i<n;i++)
    {
        a[i]=a[i]*nr+t;
        t=a[i]/BASE;
        a[i]%=BASE;
    }
    while(t)
    {
        a.push_back(t%BASE);
        t/=BASE;
    }
}
int main()
{
    fscanf(f,"%d",&L);
    rez.push_back(1);
    for(int i=2;i<L;i++)
    {
        mul(rez,i);
    }
    fprintf(g,"%d",rez[rez.size()-1]);
    for(int i=rez.size()-2;i>=0;i--)
    {
        int tmp=BASE/10;
        while(tmp>9&&rez[i]<tmp)
        {
            fprintf(g,"0");
            tmp/=10;
        }
        fprintf(g,"%d",rez[i]);
    }
    return 0;
}
