#include <cstdio>
#include <algorithm>
using namespace std;
char a[55];
char b[55];
int fr[280];
int rez;
int dist(char st,char dr)
{
    if(st<=dr)return dr-st;
    return 'Z'-st+dr-'A'+1;
}
int main()
{
   // freopen("in","r",stdin);
    fgets(a+1,55,stdin);
    fgets(b+1,55,stdin);
    for(int i=1;a[i]!='\n'&&a[i]!='\0';i++)
        fr[a[i]]++;
    for(int i=1;b[i]!='\n'&&b[i]!='\0';i++)
        fr[b[i]]--;
    for(int i='Z';i>='A';i--)
    {
        if(fr[i]<0);
        else
        {
            for(char j=(i=='Z' ? 'A':i+1);fr[i];j=(j=='Z' ? 'A':j+1))
            {
                int mini=min(fr[i],-fr[j]);
                fr[i]-=mini;
                fr[j]+=mini;
                rez+=mini*dist(i,j);
            }
        }
    }
    printf("%d",rez);
    return 0;
}
