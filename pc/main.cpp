#include <fstream>
using namespace std;
ifstream f("pc.in");
ofstream g("pc.out");
int G,V;
long long M[100][100],i,j;
int main()
{
    f>>G>>V;
    for(i=1;i<=100;i++)
    {
        M[i][0]=i;
    }
    for(i=1;i<=G;i++)
        for(j=1;j<=V;j++)
            M[i][j]=M[i-1][j-1]+M[i-1][j]+1;
    g<<M[G][V];
    f.close();
    g.close();
    return 0;
}
