# include <fstream>
# include <cstring>
# define lmax 100001
using namespace std;

ifstream f("compar.in");
ofstream g("compar.out");

int i,N,Max,Min,j,k;
char s[lmax];

int main()
{
    f.getline(s,lmax);
    N=strlen(s);
    g<<N+1<<"\n";
    Max=N+1; Min=1;
    i=0;
    while(i<N)
    {
        if (s[i]=='<')
        {
            g<<Min<<" ";
            ++Min; ++i;
        }
        else
        {
            j=i;
            while (s[j]=='>' && j<N) ++j;
            for (k=i;k<j;++k)
                {
                    g<<Max<<" ";
                    --Max;
                }
            i=j;
        }
    }
    if (s[N-1]=='<') g<<Min<<"\n";
                else g<<Max<<"\n";
    return 0;
}


