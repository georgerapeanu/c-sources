#include<fstream>
using namespace std;
ifstream f("concurs3.in");
ofstream g("concurs3.out");
int main()
{
    int h,a,n,i,gasit=0,s=0,o=0;
    f>>h>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(h==a)
            gasit=1;
        if(a/100==h/100)
            o++;
        if(a/10%10==h/10%10&&a/100==h/100)
            s++;
    }
    if(gasit==1)
        g<<"DA\n";
    else
        g<<"NU\n";
    g<<o<<"\n"<<s;
    f.close();g.close();
    return 0;
}
