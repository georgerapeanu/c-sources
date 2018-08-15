#include<fstream>
using namespace std;
ifstream f("magic6.in");
ofstream g("magic6.out");
bool gasit,l[10];
int n,i;
int main()
{
    char a;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if('a'<=a&&a<='z')
        {
            a=a-32;
            g<<a;
        }
        else
        {
            l[a-'0']=1;
        }
    }
    g<<"\n";
    for(i=0;i<10;i++)
    {
        if(l[i]==true)
        {
            if(i==0)
            {
                gasit=1;
            }
            else
            {
                g<<i;
                if(gasit==1)
                {
                    g<<0;
                    gasit=0;
                }
            }
        }
    }
    f.close();g.close();
    return 0;
}
