#include <iostream>
#include <cstring>
using namespace std;
char N[255];
int r;
int main()
{
    cin.getline(N+1,255);
    int len=strlen(N+1);
    for(int i=1;i<=len;i++)
        r=(r*10+N[i]-'0')%3;
    if(!r)
        cout<<"2";
    else
        cout<<"1\n"<<r;
    return 0;
}
