#include <iostream>
using namespace std;
int n,m,i,f,nr,f_secund,rasp[300001];
char c[300002],ch;
int main()
{
    std::cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        std::cin>>c[i];
    }
    for(i=1;i<=n;i++)
    {
        f_secund=-1;
        while(c[i]=='.')
        {
            f_secund++;i++;
        }
        if(f_secund!=-1)
        f+=f_secund;
    }
    for(i=1;i<=m;i++)
    {
        std::cin>>nr>>ch;
        if(ch=='.')
        {
            if(c[nr]!='.')
            {
                if(c[nr-1]=='.')
                f++;
                if(c[nr+1]=='.')
                f++;
            }
        }
        else
        {
            if(c[nr]=='.')
                {
                    if(c[nr-1]=='.')
                    f--;
                    if(c[nr+1]=='.')
                    f--;
                }
        }
        c[nr]=ch;
        rasp[i]=f;
    }
    for(i=1;i<=m;i++)
    std::cout<<rasp[i]<<"\n";
    return 0;
}
