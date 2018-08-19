#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;
char C[105];
int N;
unordered_map <char,int> ceva;
int f[4];
int main()
{
    cin.getline(C+1,105);
    N=strlen(C+1);
    for(int i=1;i<=N;i++)
    {
        if(C[i]!='!')
            ceva[C[i]]=i%4;
        else
            f[i%4]++;
    }
    cout<<f[ceva['R']]<<" "<<f[ceva['B']]<<" "<<f[ceva['Y']]<<" "<<f[ceva['G']];
    return 0;
}
