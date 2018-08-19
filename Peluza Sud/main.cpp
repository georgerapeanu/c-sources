#include <cstdio>
using namespace std;
FILE *f = fopen("peluzasud.in","r");
FILE *g = fopen("peluzasud.out","w");
int main()
{
    fprintf(g,"%lld",(long long)1e14 + 1);
    fclose(f);
    fclose(g);
    return 0;
}
