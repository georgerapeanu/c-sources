#include <cstdio>
using namespace std;
char C[105];
int i,j,N;
int main()
{
    scanf("%d\n",&N);
    gets(C+1);
    for(int i=1;i<=N;i++)
    {
        if(i+2<=N&&C[i]=='o'&&C[i+1]=='g'&&C[i+2]=='o')
        {
            printf("***");
            j=i+3;
            while(j+1<=N&&C[j]=='g'&&C[j+1]=='o')
                j+=2;
            i=j-1;
        }
        else
            printf("%c",C[i]);
    }
    return 0;
}
