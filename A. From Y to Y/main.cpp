#include <cstdio>
using namespace std;
long long K;
char c='a';
int main()
{
    scanf("%I64d",&K);
    if(!K)
    {
        printf("a");
        return 0;
    }
    while(K)
    {
        long long st=1,dr=1000;
        while(st<dr)
        {
            long long mid=(st+dr+1)/2;
            if(K>=(mid-1)*mid/2)
            {
                st=mid;
            }
            else
            {
                dr=mid-1;
            }
        }
        K-=st*(st-1)/2;
        for(int i=1;i<=st;i++)fputc(c,stdout);
        c++;
    }
    return 0;
}
