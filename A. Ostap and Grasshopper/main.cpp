#include <cstdio>
#include <algorithm>
using namespace std;
char A[105];
int N,K,st,dr;
int main()
{
    scanf("%d %d\n",&N,&K);
    gets(A+1);
    for(int i=1;i<=N;i++)
    {
        if(A[i]=='G')
            st=i;
        else if(A[i]=='T')
            dr=i;
    }
    if(st>dr)
        swap(st,dr);
    if((dr-st)%K!=0)
    {
        printf("NO");
        return 0;
    }
    for(int i=st;i<=dr;i+=K)
    {
        if(A[i]=='#')
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
