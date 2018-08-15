#include <iostream>

using namespace std;
int S[100005][31];
int N;
int a;
int nr,rez=1<<30;
int check(int st,int dr)
{
    int nr=0;
    for(int b=0;b<=30;b++)
        nr+=(S[dr][b]-S[st-1][b]!=0);
    return nr;
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        for(int b=0;b<=30;b++)
        {
            S[i][b]=S[i-1][b]+((a>>b)&1);
            if(i==N)nr+=(S[i][b]!=0);
        }
    }
    for(int i=1;i<=N;i++)
    {
        int st=i,dr=N+1;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            if(check(i,mid)<nr)st=mid+1;
            else dr=mid;
        }
        if(dr==N+1)continue;
        rez=min(rez,dr-i+1);
    }
    cout<<rez;
    return 0;
}
