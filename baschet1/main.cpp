#include <fstream>
#include <iostream>
using namespace std;
ifstream f("baschet1.in");
ofstream g("baschet1.out");
int n,c=1,nr,i,cnr,a,b=3,gasit;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        gasit=0;b=3;c=1;
        f>>nr;cnr=nr;cout<<nr<<" ";
        while(cnr!=0)
        {
            cnr=cnr/10;
            c=c*10;
        }
        c=c/10;
        while(c!=0)
        {
           a=nr/c;
           nr=nr%c;
            if(b!=3)
            {
                if((a!=0)&&(b!=0))
                {
                    if(a!=b)
                        {gasit=1;break;}
                }
            }
            c=c/10;
            b=a;
        }
        if(gasit==1)
            g<<"eroare"<<"\n";
        else
            g<<"\n";
    }
    f.close();
    g.close();
    return 0;
}
