#include <cstdio>
#include <algorithm>
using namespace std;
int N;
char C[205];
int rez,tmp;
int main()
{
    scanf("%d\n",&N);
    fgets(C+1,205,stdin);
    for(int i=1;i<=N;i++)
    {
        if(('a'<=C[i]&&C[i]<='z')||('A'<=C[i]&&C[i]<='Z'))
        {
            tmp+=('A'<=C[i]&&C[i]<='Z');
        }
        else
        {
            tmp=0;
        }
        rez=max(tmp,rez);
    }
    printf("%d",rez);
    return 0;
}
