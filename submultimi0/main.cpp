#include <fstream>
using namespace std;
ifstream f("submultimi.in");
ofstream g("submultimi.out");
int N,top,st[20];
void back(int k)
{
    if(k==N+1){
        //afisare
        if(top!=0)
        {
            for(int i=1;i<=top;i++)
                g<<st[i]<<" ";
            g<<"\n";
        }
    }
    else
    {
        back(k+1);
        st[++top]=k;
        back(k+1);
        --top;
    }
}
//int nr=1,n,cnr,maxim,poz;
/*
int main()
{
    f>>n;
    maxim=1<<n;
    for(nr=1;nr<maxim;nr++)
    {
        for(poz=0;poz<n;poz++)
        {
            if(nr&(1<<poz))
                g<<poz+1<<" ";
        }
        g<<"\n";
    }
    f.close();
    g.close();
    return 0;
}
*/
int main()
{
    f>>N;
    back(1);
    f.close();
    g.close();
    return 0;
}
