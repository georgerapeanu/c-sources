#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
FILE *g=fopen("magic4.out","w");
int N;
int main()
{
    srand(time(NULL));
    N=rand()%100000+1;
    while(N)
    {fprintf(g,"1\n");N--;}
    fclose(g);
    return 0;
}
