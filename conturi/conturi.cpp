#include<fstream>
using namespace std;
ifstream f("conturi.in");
ofstream d("conturi.out");
int main()
{
    int i,c,g,b,s,n,x,maxi=0;
    f>>n>>x;
    for(i=1;i<=n;i++)
    {
        f>>c;
        b=c/100000;
        g=c/10000%10;
        s=c%10000;
        if(b==x)
        {
            if(g==1)
            {
                if(s>maxi)
                    maxi=s;
            }
        }
    }
    d<<maxi;
    f.close();d.close();
    return 0;
}
