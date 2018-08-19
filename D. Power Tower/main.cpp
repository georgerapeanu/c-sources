#include <iostream>
#include <vector>
using namespace std;
vector<int> phi;
long long N,M,Q;
long long W[100005];
long long getphi(long long A){
    long long phi = A;
    for(long long d = 2;1LL * d * d <= A;d++){
        if(A % d == 0){
            phi = phi / d * (d - 1);
            while(A % d == 0){
                A /= d;
            }
        }
    }
    if(A != 1){
        phi = phi / A * (A - 1);
    }
    return phi;
}
long long mod(long long a,long long b){
    if(a < b){
        return a;
    }
    return a % b + b;
}
long long lgpow(long long b,long long e,long long MOD){
    long long p = 1;
    while(e){
        if(e & 1){
            p = mod(1LL * b * p,MOD);
        }
        b = mod(1LL * b * b,MOD);
        e >>= 1;
    }
    return p;
}
long long solve(long long x,long long y,long long pos){
    if(x > y || pos >= (int)phi.size()){
        return 1;
    }
    return lgpow(W[x],solve(x + 1,y,pos + 1),phi[pos]);
}
int main()
{
//    cin.sync_with_stdio(false);cin.tie(0);
//    cout.sync_with_stdio(false);cout.tie(0);
    cin >> N >> M;
    phi.push_back(M);
    while(phi.back() != 1){
        phi.push_back(getphi(phi.back()));
    }
    for(long long i = 1;i <= N;i++){
        cin >> W[i];
    }
    cin >> Q;
    while(Q--){
        long long x,y;
        cin >> x >> y;
        cout << solve(x,y,0) % M << "\n";
    }
    return 0;
}
