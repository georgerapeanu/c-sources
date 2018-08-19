#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
set<int> S;
int N;
int V[100005];
int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a % b);
}
int L[200005];
int LL[2000005];
bool ok(int pref){
    memset(L,0,sizeof(L));
    for(int i = 1;i <= pref;i++){
        L[V[i]]++;
    }
    if(L[1]){
        return 0;
    }
    for(int i = 2;i <= 100000;i++){
        int cnt = 0;
        for(int j = i;j <= 100000;j += i){
            cnt += L[j];
            if(cnt > 1){
                return 0;
            }
        }
    }
    return 1;
}
int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
    }
    int st = -1,dr = N + 1;
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(ok(mid)){
            st = mid;
        }
        else{
            dr = mid;
        }
    }
    for(int i = 1;i <= st;i++){
        cout << V[i] << " ";
    }
     for(int i = 1;i <= st;i++){
        L[V[i]]++;
    }
    for(int i = 2;i <= 200000;i++){
        for(int j = i;j <= 200000;j += i){
            LL[i] += L[j];
        }
    }
    int val = V[st + 1] + 1;
    while(LL[val]){
        val++;
    }
    cout << val << " ";
    for(int i = 1;i <= 100000;i++){
        LL[i] += (val % i == 0);
    }
    return 0;
}
