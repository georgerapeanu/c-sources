#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("heapsort.in");
ofstream g("heapsort.out");
int p,c,N,nh,H[100000],i;
int main()
{
    H[0]=10000000;
    f>>N;
    for(i=1;i<=N;i++)
    {
        f>>H[i];
        c=i;
        p=c/2;
        while(1)
        {
            if(H[p]>H[c])
                break;
            if(p<1)
                break;
            swap(H[p],H[c]);
            c=p;
            p=p/2;
        }
    }
    nh=N;
    for(i=1;i<=N;i++)
    {
        swap(H[1],H[nh]);
        nh--;
        p=1;
        c=p*2;
        while(1)
        {
            if(H[c]<H[c+1]&&c+1<=nh)
                c++;
            if(c>nh)
                break;
            if(H[c]<H[p])
                break;
            swap(H[c],H[p]);
            p=c;
            c*=2;
        }
    }
    for(i=1;i<=N;i++)
        g<<H[i]<<" ";
    f.close();
    g.close();
    return 0;
}
