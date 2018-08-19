#include <cstdio>
using namespace std;
char C[20];
char home[20];
int a,b;
int N;
int main()
{
    scanf("%d\n",&N);
    gets(home);
    for(int i=1;i<=N;i++)
    {
        gets(C);
        if(C[0]==home[0]&&C[1]==home[1]&&C[2]==home[2])
            a++;
        else
            b++;
    }
    if(a==b) puts("home");
    else puts("contest");
    return 0;
}
