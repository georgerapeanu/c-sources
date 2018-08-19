#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("eqs.in","r");
FILE *g=fopen("eqs.out","w");
int a1,a2,a3,a4,a5;
int rez;
vector<int> S;
int main()
{
    fscanf(f,"%d%d%d%d%d",&a1,&a2,&a3,&a4,&a5);
    for(int i=-50;i<=50;i++)
        for(int j=-50;i&&j<=50;j++)
            if(j)
                S.push_back(a4*i*i*i+a5*j*j*j);
    sort(S.begin(),S.end());
    for(int i=-50;i<=50;i++)
        for(int j=-50;i&&j<=50;j++)
            for(int k=-50;i&&j&&k<=50;k++)
                if(k)
                    rez+=distance(lower_bound(S.begin(),S.end(),-i*i*i*a1-j*j*j*a2-k*k*k*a3),upper_bound(S.begin(),S.end(),-i*i*i*a1-j*j*j*a2-k*k*k*a3));
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
