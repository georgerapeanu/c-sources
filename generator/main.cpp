#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
FILE *f=fopen("test.in","w");
int N=(int) 1e6;
const long long M= (long long) 1e17;
const long long m= -(long long) 1e17;
int main()
{
    srand(0);
    fprintf(f,"%d",N);
    for(int i=1;i<=N;i++)
    {
        fprintf(f,"%lld\n",rand()%(M-m+1)+m);
    }
    return 0;
}
