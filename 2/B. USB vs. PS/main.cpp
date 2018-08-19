#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
char C[20];
int a,b,c,val;
vector<int> A,B;
int N;
long long nr,sum;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    scanf("%d %d %d\n",&a,&b,&c);
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d %s",&val,C);
        if(C[0]=='U') A.push_back(val);
        else B.push_back(val);
    }
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    val=A.size();
    a=min(val,a);
    val=B.size();
    b=min(val,b);
    for(int i=0;i<a;i++) {sum+=A[i];nr++;}
    for(int i=0;i<b;i++) {sum+=B[i];nr++;}
    A.push_back(1<<30);
    B.push_back(1<<30);
    int i1=a,i2=b;
    while(c)
    {
        if(A[i1]==B[i2]&&A[i1]==(1<<30))
            break;
        if(A[i1]<B[i2]){sum+=A[i1++];}
        else {sum+=B[i2++];}
        nr++;
        c--;
    }
    cout<<nr<<" "<<sum;
    return 0;
}
