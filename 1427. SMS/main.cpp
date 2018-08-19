#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#define NMAX 100005
using namespace std;
char C[NMAX];
int N,M,len,uc;
int D[NMAX];
bool issomething(char c)
{
    if(isalpha(c)||c==' ')
        return 0;
    return 1;
}
int main()
{
    cin>>N>>M;
    cin.getline(C+1,NMAX);
    cin.getline(C+1,NMAX);
    len=strlen(C+1);
    for(int i=1;i<=len;i++)
    {
        if(issomething(C[i]))
        {
            uc=i;
            D[i]=D[max(0,i-N)]+1;
        }
        else
        {
            D[i]=min(D[max(uc,i-M)],D[max(0,i-N)])+1;
        }
    }
    cout<<D[len];
    return 0;
}
