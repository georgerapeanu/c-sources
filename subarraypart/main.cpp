#include <iostream>
#include <algorithm>
using namespace std;
int N,A[100005];
int v1[100005];
int v2[100005];
int fst[100005];
int lst[100005];
bool cmp(int a,int b)
{
    if(a<0&&b>0)return 1;
    if(a>0&&b<0)return 0;
    return (abs(a)<abs(b));
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int a;
        cin>>a;
        if(!fst[a])fst[a]=i;
        lst[a]=i;
    }
    for(int i=1;i<=100000;i++)
    {
        if(fst[i])
        {
            v1[fst[i]]++;
            v2[lst[i]]++;
        }
    }
    int nr=0,rez=1;
    for(int i=1;i<=N;i++)
    {
        nr+=v1[i];
        nr-=v2[i];
        if((v1[i]||v2[i])&&nr==0)rez++;
    }
    cout<<rez;
    return 0;
}
