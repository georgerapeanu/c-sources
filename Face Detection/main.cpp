#include <iostream>
using namespace std;
short n,m,nr,i,j;
char c[51][51];
bool ap[26];
int main()
{
    std::cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            std::cin>>c[i][j];
        }
    }
    for(i=1;i<n;i++)
    {
        for(j=1;j<m;j++)
        {
            ap[c[i][j]-'a']=1;
            ap[c[i+1][j]-'a']=1;
            ap[c[i][j+1]-'a']=1;
            ap[c[i+1][j+1]-'a']=1;
            if(ap[0]==1&&ap[5]==1&&ap[4]==1&&ap[2]==1)
            {
                nr++;
            }
            ap[0]=ap[2]=ap[4]=ap[5]=0;
        }
    }
    std::cout<<nr;
    return 0;
}
