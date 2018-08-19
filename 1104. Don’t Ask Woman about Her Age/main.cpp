#include <iostream>
#include <cstring>
#define val(c) ('0'<=c&&c<='9' ? c-'0':10+c-'A')
using namespace std;
char N[1000005];
int len;
int main()
{
    cin.getline(N+1,1000005);
    len=strlen(N+1);
    int nr=0,k=1;
    for(int i=1;i<=len;i++)
        nr+=val(N[i]),k=max(k,val(N[i]));
    while(k<=36&&nr%k!=0) k++;
    k++;
    if(k>36) cout<<"No solution.";
    else     cout<<k;
    return 0;
}
