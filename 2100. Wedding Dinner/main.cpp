#include <cstdio>
#include <cstring>
using namespace std;
char C[65];
int N,nr=2;
int main()
{
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        gets(C+1);
        int len=strlen(C+1);
        int j=1;
        while(j<=len&&C[j]!='+')
            j++;
        if(C[j]=='+')
            nr++;
        nr++;
    }
    if(nr==13)
        nr++;
    printf("%d",nr*100);
    return 0;
}
