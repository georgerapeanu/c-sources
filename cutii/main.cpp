#include <fstream>
using namespace std;
ifstream f("cutii.in");
ofstream g("cutii.out");
short cl,j,cd,i,n,k,l[1001],d[1001],afis[2][1001];
bool u[1001];
int main()
{
    f>>n>>k;
    for(i=1;i<=n;i++)
    f>>l[i]>>d[i];
    for(i=1;i<=k;i++)
    {
        f>>cl>>cd;
        j=1;
        while(j<=n)
        {
            if(u[j]==false&&l[j]<=cl&&d[j]<=cd)
            {
                u[j]=true;
                afis[0][0]++;
                afis[0][afis[0][0]]=j;
                afis[1][afis[0][0]]=i;
                break;
            }
            j++;
        }
    }
    g<<afis[0][0]<<"\n";
    for(i=1;i<=afis[0][0];i++)
    g<<afis[0][i]<<" "<<afis[1][i]<<"\n";
    f.close();
    g.close();
    return 0;
}
