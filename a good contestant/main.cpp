#include <cstdio>
using namespace std;
char C[10];
int nr1,nr2,N;
bool ok;
int main()
{
    scanf("%d",&N);
    while(N--)
    {
        scanf("%s %d %d",&C,&nr1,&nr2);
        if(nr1>=2400&&nr1<nr2)
        {
            ok=1;
        }
    }
    if(!ok)
        printf("NO");
    else
        printf("YES");
    return 0;
}
