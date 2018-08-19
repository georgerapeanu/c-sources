#include <cstdio>
using namespace std;
int t[100][100][100];
FILE *f,*g;
int n,m,p;
int main()
{
    f=fopen("3d.in","r");
    g=fopen("3d.out","w");
    f>>n>>m>>p;
    fclose(f);
    fclose(g);
    return 0;
}
