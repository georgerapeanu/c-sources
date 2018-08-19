#include <iostream>
#include <cstring>
using namespace std;
char C[20];
int  S[20];
int N;
long long rez=1;
int main() {
    cin.getline(C+1,20);N=strlen(C+1);N-=(C[N]=='\n');
    for(int i=1;i<=N;i++)S[i]=C[i]-'0';
    for(int i=1;i<N;i++)
    {
        int val;
        cin>>val;
        if(val){S[N-i+1]+=10;S[N-i]-=1;}
    }
    for(int i=1;i<=N;i++)
    {
        if(S[i]<0||S[i]>18)cout<<0;
        int st=max(0,S[i]-9),dr=min(S[i],9);
        rez*=(dr-st+1);
    }
    cout<<rez;
    return 0;
}
