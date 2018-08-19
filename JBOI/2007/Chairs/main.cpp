#include <cstdio>
#include <algorithm>
using namespace std;
int Ev[24*60*60+5];
int h1,m1,s1,h2,m2,s2;
int N;
int main()
{
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d:%d:%d %d:%d:%d\n",&h1,&m1,&s1,&h2,&m2,&s2);
        int t1=h1*60*60+m1*60+s1;
        int t2=h2*60*60+m2*60+s2;
        Ev[t1]++;
        Ev[t2+1]--;
    }
    int act=0,rez=0;
    for(int i=0;i<=24*60*60+1;i++)
    {
        act+=Ev[i];
        rez=max(act,rez);
    }
    printf("%d",rez);
    return 0;
}
