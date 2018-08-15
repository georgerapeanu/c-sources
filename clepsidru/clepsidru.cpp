#include<fstream>
using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");
int main()
{
    int i,t,b,n,k,s1=0;
    f>>n>>b>>k;
    int s[k],p[k];
    t=b+n-1;
    g<<t<<"\n";
    for(i=0;i<k;i++)
    {
        f>>s[i]>>p[i];
        if(p[i]==1)
            s1+=s[i];
        else
            s1-=s[i];
    }

        f.close();g.close();
        return 0;
}
