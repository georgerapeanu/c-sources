#include<fstream>
using namespace std;
ifstream f("robinson.in");
ofstream g("robinson.out");
int main()
{
    int gasit=0,r,i,j,m,n,l,c,y=1,k[y],v[y];
    f>>m>>n>>l>>c;
    int a[m][m];
    for(i=0;i<m;i++)
    {
        a[0][i]=n+i;
        a[i][0]=n+i;
    }
    for(i=1;i<m;i++)
    {
        for(j=1;j<m;j++)
        {
            a[i][j]=(a[i-1][j]+a[i][j-1])%1000;
        }
    }
    g<<a[m-1][m-1]<<"\n";
    while(gasit==0)
    {
        if(y!=1)
        {
            for(i=0;i<y-1;i++)
            {
                if(l==k[i]&&c==v[i])
                {
                    gasit=1;
                }
            }
                k[y-1]=l;
                v[y-1]=c;
                y++;
        }
        else
        {
            k[y-1]=l;
            v[y-1]=c;
            y++;
        }
        if(gasit==0)
        {
        g<<l<<" "<<c<<"\n";
        r=a[l-1][c-1]%4;
        switch(r)
        {
            case 0:l--;
            break;
            case 1:c++;
            break;
            case 2:l++;
            break;
            case 3:c--;
            break;
        }
        }
        if(c==0)
           {gasit=1;}
        if(l==0)
            {gasit=1;}
        if(c>m)
          {gasit=1;}
        if(l>m)
         {gasit=1;}
    }
    f.close();g.close();
    return 0;
}
