#include <fstream>
#include <iostream>
using namespace std;
ifstream f("furnica.in");
ofstream g("furnica.out");
int n,k,v,i=1,j=1,l,s,a[102][102],minim,nr=1;
int main()
{
    f>>n>>k;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            a[i][j]=(i+j)%6;
        }
    }
    i=1;j=1;
for(l=1;l<=k;l++)
{
    if(a[i][j]>=0)
    {s+=a[i][j];a[i][j]=-1;}
    else
        a[i][j]--;
    f>>v;
     switch(v)
        {
            case 1:i--;
            break;
            case 2:i--;j++;
            break;
            case 3:j++;
            break;
            case 4:j++;i++;
            break;
            case 5:i++;
            break;
            case 6:j--;i++;
            break;
            case 7:j--;
            break;
            case 8:j--;i--;
            break;
        }
}
if(a[i][j]>=0) {s=s+a[i][j];a[i][j]=-1;} else a[i][j]=a[i][j]-1;
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
    if(a[i][j]==minim)
        nr++;
    if(a[i][j]<minim)
    {
        minim=a[i][j];nr=1;
    }
}
g<<s<<" "<<nr;
    f.close();g.close();
    return 0;
}
