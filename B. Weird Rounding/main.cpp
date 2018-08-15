#include <cstdio>
#include <cstring>
using namespace std;
char N[20];
int k;
int main()
{
    scanf("%s %d",N+1,&k);
    int len=strlen(N+1);
    len=len-(N[len]=='\n');
    int nr=0,clen=len;
    while(len>0&&k>0)
    {
        if(N[len]=='0')
            k--;
        else
            nr++;
        len--;
    }
    if(k==0)
        printf("%d",nr);
    else printf("%d",clen-1);
    return 0;
}
