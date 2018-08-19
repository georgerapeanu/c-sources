#include <iostream>
using namespace std;
char ch;
bool gasit,v[101][101];
int j,i,rasp[101],nr,n,igor[101],trim[101];
int main()
{
    std::cin>>n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            std::cin>>ch;
            v[i][j]=ch-'0';
        }
    }
    for(i=1;i<=n;i++)
    std::cin>>igor[i];
    for(i=1;i<=n;i++)
    {
        gasit=0;
        for(j=1;j<=n;j++)
        {
            if(v[i][j]==1)
            {
                if(trim[j]+1==igor[j])
                {
                    gasit=1;break;
                }
            }
        }
        if(!gasit)
        {
            nr++;
            rasp[nr]=i;
            for(j=1;j<=n;j++)
               if(v[i][j]==1)
            {
                trim[j]++;
            }
        }
    }
        std::cout<<nr<<"\n";
        for(i=1;i<=nr;i++)
        std::cout<<rasp[i]<<" ";

    return 0;
}
