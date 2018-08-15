#include <cstdio>
#include <algorithm>
using namespace std;
int T,tmp,maxi;
int ceva[100005];
char C[100005];
bool ok(int tmp)
{
    int nr=tmp;
    for(int i=1;i<=ceva[0];i++)
    {
        if(!nr)nr=tmp;
        if(nr<ceva[i])return 0;
        nr-=ceva[i];
    }
    return 1;
}
int main()
{
    freopen("in","r",stdin);
    scanf("%d\n",&T);
    while(T--)
    {
        ceva[0]=1;tmp=0;maxi=0;
        fgets(C+1,100005,stdin);
        for(int i=1;C[i]!='\0'&&C[i]!='\n';i++)
        {
            if(C[i]!=' '){ceva[ceva[0]]++;tmp++;maxi=max(maxi,ceva[ceva[0]]);}
            else ceva[0]++;
        }
        for(int i=maxi;i*i<=tmp;i++)
        {
            if(tmp%i==0&&(ok(i)||ok(tmp/i)))
            {
                printf("YES\n");
            }
        }
        printf("NO\n");
    }
    return 0;
}
