#include <bits/stdc++.h>

using namespace std;

int t;
vector<long long> angles;

const long long MOD = (360 * 12LL) * (10000000000LL);
const long long HOUR_TICKS = MOD / 12;
const long long MINUTE_TICKS = HOUR_TICKS / 60;
const long long SECOND_TICKS = MINUTE_TICKS / 60;

const long long inv11 = 15709090909091;

long long add(long long a,long long b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

long long scad(long long a,long long b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

long long mult(long long a,long long b){
    return a * b % MOD;
}

int main(){

    scanf("%d",&t);

    for(int test = 1;test <= t;test++){
        printf("Case #%d: ",test);
        angles = vector<long long>(3,0);
        scanf("%lld %lld %lld",&angles[0],&angles[1],&angles[2]);
        long long  _t;

        do{
            ///angles[0] = t - a
            ///angles[1] = 12 * t - a
            long long a = mult(scad(0,scad(mult(12,angles[0]),angles[1])),inv11);
            long long _t = add(angles[0],a);
            if(_t >= a && scad(_t,a) == angles[0] && scad(mult(12,_t),a) == angles[1] && scad(mult(720,_t),a) == angles[2]){
                long long h = _t / HOUR_TICKS;
                long long m = (_t % HOUR_TICKS) / MINUTE_TICKS;
                long long s = (_t % MINUTE_TICKS) / SECOND_TICKS;
                long long n = (_t % SECOND_TICKS);
                printf("%lld %lld %lld %lld",h,m,s,n);
                break;
            }
        }while(next_permutation(angles.begin(),angles.end()));

        printf("\n");
    }

    return 0;
}
