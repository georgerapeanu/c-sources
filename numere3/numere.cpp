#include<fstream>
using namespace std;
ifstream f("numere.in");
ofstream g("numere.out");
int main()
{
    int gasit=0,n,i,maxcifra,mincifra,uc,s=0,j=0,k,r,c=1,d;
    f>>n;
    long a,ca;
    for(i=0;i<n;i++)
    {
        f>>a;
        gasit=0;j=0;
        maxcifra=0;
        mincifra=9;c=1;
        ca=a;
        while(ca!=0)
        {
            uc=ca%10;
            ca=ca/10;
            if(uc>maxcifra)
                maxcifra=uc;
        }
        mincifra=a%10;
        a=a/10;
        ca=a;
        while(gasit==0)
        {
            uc=ca%10;ca=ca/10;
            if(uc==maxcifra)
                gasit=1;
                j++;
        }
        for(k=1;k<j;k++)
            c*=10;
        r=a%c;
        a=a/c;
        d=a%10;
        a=a/10;
        d=mincifra;
        a=a*10+d;
        a=a*c+r;
        s+=mincifra;
        g<<a<<"\n";
    }
    g<<s;
    f.close();g.close();
    return 0;
}
