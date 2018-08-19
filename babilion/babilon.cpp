#include<fstream>
using namespace std;
ifstream f("babilon.in");
ofstream g("babilon.out");
int main()
{
    int p,n;
    f>>p>>n;
    if(p==1)
    {
        int v[n],nr=0,nrmaxim=0,i,j=0;
        for(i=0;i<n;i++)
            f>>v[i];
        for(i=0;i<n;i++)
        {
            j=0;nr=0;
            while(v[i+j]==1)
            {
                j++;
                nr++;
            }
            if(nr>nrmaxim)
                nrmaxim=nr;
        }
        g<<nrmaxim;
    }
    else
    {
        int a,b,z=0,i;
        f>>a;
        if(a==1) z+=1;
        else if(a==2) z+=10;
        else
            z=0;
        for(i=2;i<=n;i++)
        {
            f>>b;
            if (b>a) z=z*60;
            if(b==1)z++;
                else if(b==2)z+=10;
            if (b!=3)   a=b;
        }
        g<<z;
    }
    f.close();g.close();
    return 0;
}
