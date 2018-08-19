#include <iostream>
#include <iomanip>
using namespace std;
long long k,d,t;
long long timeForBlock;
long long numBlocks;
long double ans;
int main(){
    cin >> k >> d >> t;
    t *= 2;
    d = (k / d + (k % d != 0)) * d;
    timeForBlock = k * 2 + (d - k);
    numBlocks = t / timeForBlock;
    t -= numBlocks * timeForBlock;
    ans = d * numBlocks;
    if(2 * k >= t){
        ans += (long double)t / 2;
    }
    else{
        ans += (long double)k + (t - 2 * k);
    }
    cout << fixed << setprecision(9) << ans;
    return 0;
}
