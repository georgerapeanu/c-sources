#include <fstream>
using namespace std;
ifstream f("film.in");
ofstream g("film.out");
int F,B,k,i;
char c[300];
int main()
{
    f>>F>>B;
    if(B<F)
    {
        k=F-B;
        for(i=0;i<k;i++)
        {c[3*i]='f';c[3*i+1]='b';c[3*i+2]='f';}
        for(i=3*k;i<B+F;i+=2)
        {
            c[i]='b';
            c[i+1]='f';
        }
    }
    else
    {
       k=F-B;
        for(i=0;i<k;i++)
        {c[3*i]='b';c[3*i+1]='f';c[3*i+2]='b';}
        for(i=3*k;i<B+F;i+=2)
        {
            c[i]='f';
            c[i+1]='b';
        }
    }
    g<<c;
    f.close();
    g.close();
    return 0;
}
