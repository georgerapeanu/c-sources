#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
    srand(0);
    for(int i=1;i<=1000000;i++)
        putc('a'+rand()%26,stdout);
    return 0;
}
