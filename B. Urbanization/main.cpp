#include <cstdio>
#include <algorithm>
using namespace std;
int N,n1,n2,V[100005];
double rez=0;
int main()
{
    scanf("%d %d %d",&N,&n1,&n2);
    for(int i=1;i<=N;i++)
        scanf("%d",&V[i]);
    sort(V+1,V+1+N);
    if(n2<n1)
        swap(n1,n2);
    for(int i=N;i>N-n1;i--)
    {
        rez+=double(V[i])/n1;
    }
    for(int i=N-n1;i>N-n1-n2;i--)
    {
        rez+=double(V[i])/n2;
    }
    printf("%.6f",rez);
    return 0;
}
