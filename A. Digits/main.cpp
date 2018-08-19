#include <cstdio>
#include <algorithm>
using namespace std;
int N;
char C[200005];
int sum=0;
void inttochar(char C[],int val)
{
    N=0;
    if(!val){C[1]=0;N=1;return ;}
    while(val)
    {
        C[++N]=val%10;
        val/=10;
    }
    reverse(C+1,C+1+N);
}
int main()
{
    scanf("%d\n",&N);
    fgets(C+1,200000,f);
    for(int i=1;i<=N;i++)
    {

    }
    return 0;
}
