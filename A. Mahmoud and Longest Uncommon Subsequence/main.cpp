#include <iostream>
#include <cstring>
using namespace std;
char A[100005];
char B[100005];
int main()
{
    cin.getline(A,100003);
    cin.getline(B,100003);
    if(strcmp(A,B)==0) cout<<"-1";
    else cout<<max(strlen(A),strlen(B));
    return 0;
}
