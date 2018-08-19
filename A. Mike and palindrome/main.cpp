#include <iostream>
#include <cstring>
using namespace std;
char C[60];
int N;
int nreval(int st,int dr)
{
    if(st>dr)return 0;
    return ((C[st]!=C[dr])+nreval(st+1,dr-1));
}
int main()
{
    cin.getline(C+1,60);
    N=strlen(C+1);
    if(nreval(1,N)!=1&&(!(nreval(1,N)==0&&N%2==1)))
        cout<<"NO";
    else
        cout<<"YES";
    return 0;
}
