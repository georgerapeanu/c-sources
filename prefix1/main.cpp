#include <fstream>
using namespace std;
int K,fr[200],r,nr,maxim,i;
ifstream f("prefix1.in");
ofstream g("prefix1.out");
char c;
int main()
{
    f>>K;
    while(f>>c)
    {
        r=r*10+c-'0';
        r%=K;
        fr[r]++;
    }
    for(i=0;i<K;i++)
    {
        if(fr[i]>maxim)
        {
            maxim=fr[i];
            nr=i;
        }
    }
    g<<nr<<" "<<maxim;
    f.close();
    g.close();
    return 0;
}
