#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;
unordered_map<int,int> M;
int N;
char S[100005];
long long rez;
bool leading;
int main() {
    cin.getline(S+1,100005);
    int sum=0;
    N=strlen(S+1);
    M[0]=1;
    leading=(S[1]=='0');
    for(int i=1;i<=N;i++)
    {
        sum=(sum+S[i]-'0')%3;
        rez+=((S[i]-'0')%2==0)*(M[sum]-(sum==0&&leading==1));
        if(S[i+1]!='0')
            M[sum]++;
        rez+=(S[i]=='0');
    }
    cout<<rez;
    return 0;
}
