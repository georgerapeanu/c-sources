#include <fstream>
using namespace std;
ifstream f("readunare.in");
ofstream g("readunare.out");
string A[2],a,b;
int sum;
void scrie(int nr)
{
    if(nr==0)
        return ;
    if(nr==1)
    {g<<"{}";return ;}
    g<<"{";
    scrie(nr-1);
    g<<"},";
    scrie(nr-1);
}
int main()
{
    f>>a>>b;
    if(a.size()==2)
        ;
    else
    {
        int nrp=-1;
        sum++;
        for(auto it:a)
        {
            if(it=='{')
                nrp++;
            else if(it=='}')
                nrp--;
            if(nrp==0&&it==',')
                sum++;
        }
    }
    if(b.size()==2)
    {
        ;
    }
    else
    {
        int nrp=-1;
        sum++;
        for(auto it:b)
        {
            if(it=='{')
                nrp++;
            else if(it=='}')
                nrp--;
            if(nrp==0&&it==',')
                sum++;
        }
    }
    g<<"{";
    scrie(sum);
    g<<"}";
    f.close();
    g.close();
    return 0;
}
