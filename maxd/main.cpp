#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
FILE *f=fopen("maxd.in","r");
FILE *g=fopen("maxd.out","w");
int a,b;
bitset<100000> B;
vector<int> P;
int mini,ctr,nr;
int main()
{
    B[0]=B[1]=1;
    for(int i=2;i*i<100000;i++)
    {
        if(!B[i])
        {
            for(int j=i*i;j<100000;j+=i)
                B[j]=1;
            P.push_back(i);
        }
    }
    fscanf(f,"%d%d",&a,&b);
    for(int i=a;i<=b;i++)
    {
        int nrdiv=1;
        int ti=i;
        for(auto it:P)
        {
            if(it>ti)
                break;
            int exp=1;
            while(ti%it==0)
            {
                exp++;ti/=it;
            }
            nrdiv*=exp;
        }
        nrdiv*=(1+(ti>1));
        if(nrdiv>nr){nr=nrdiv;ctr=1;mini=i;}
        else if(nrdiv==nr) ctr++;
    }
    fprintf(g,"%d %d %d",mini,nr,ctr);
    fclose(f);
    fclose(g);
    return 0;
}
