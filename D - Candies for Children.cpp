#include <iostream>

using namespace std;

long long n,l,r,k;

const int LIM = 1e6;
long long d;

long long dist(long long l,long long r){
    if(l <= r){
        return r - l + 1;
    }
    return n - (l - r - 1);
}

bool ok(long long ans){

    if(ans < 0){
        return false;
    }

    long long z = k - d;

    if(z < 0){
        return false;
    }

    long long c = z / (n + ans);
    long long y = z - c * (n + ans);
    long long low = max(0LL,ans - n + d);
    long long hi = min(ans,d);

    if(low <= y && y <= hi){
        return true;
    }
    else if(low <= y + 1 && y + 1 <= hi){
        return true;
    }
    return false;
}

int main(){

    cin >> n >> l >> r >> k;

    long long ans = -1;
    d = dist(l,r);

    if(k - d <= d){
        ans = ok(min(d,k - d + 1) + n - d) ? min(d,k - d + 1) + n - d:-1;
    }

    for(int c = 0;c <= LIM;c++){
        long long z = k - c * n - d;

        if(z < 0){
            continue;
        }

        long long ans1 = (z + n - d) / (c + 1);
        long long ans2 = z / (c + 1);

        for(long long a = ans1 - 10;a <= ans1 + 10;a++){
            if(ok(a)){
                ans = max(ans,a);
            }
        }

        for(long long a = ans2 - 10;a <= ans2 + 10;a++){
            if(ok(a)){
                ans = max(ans,a);
            }
        }
    }

    for(long long a = 0;a <= LIM;a++){
        if(ok(a)){
            ans = max(ans,a);
        }
    }

    cout << ans;

    return 0;
}