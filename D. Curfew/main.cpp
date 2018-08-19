#include <cstdio>
#include <algorithm>
using namespace std;
int N,B,D;
int A[100005];
long long S[100005];
long long debtL;
long long debtR;
int main(){
    scanf("%d %d %d",&N,&D,&B);
    for(int i = 1;i <= N;i++){
        scanf("%d",&A[i]);
        S[i] = A[i] + S[i - 1];
    }
    for(int st = 1,dr = N;st < dr;st++,dr--){
        if(S[])
    }
    return 0;
}
