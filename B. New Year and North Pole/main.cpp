#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int poz;
int N;
char C[10];
int val;
int ok=1;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        scanf("%d %s",&val,C);
        if(ok)
        {
            if(!poz)
            {
                if(strcmp(C,"South")!=0)
                {
                    ok=0;
                }
            }
            else if(poz==20000)
            {
                if(strcmp(C,"North")!=0)
                {
                    ok=0;
                }
            }
            if(strcmp(C,"South")==0)
            {
                poz+=val;
                if(poz>20000)
                {
                    ok=0;
                }
            }
            else if(strcmp(C,"North")==0)
            {
                poz-=val;
                if(poz<0)
                {
                    ok=0;
                }
            }
        }
    }
    if(poz!=0||!ok)
        cout<<"NO";
    else
        cout<<"YES";
    return 0;
}
