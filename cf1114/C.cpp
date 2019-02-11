#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long n,b;

vector< pair<long long,int> > desc;

int main() {

    cin >> n >> b;

    for(int i = 2; 1LL * i * i <= b; i++) {
        if(b % i == 0) {
            desc.push_back({i,0});
            while(b % i == 0) {
                b /= i;
                desc.back().second++;
            }
        }
    }

    if(b != 1) {
        desc.push_back({b,1});
    }

    long long ans = 1LL << 60;

    for(auto it:desc) {
        long long exp = 0;

        for(long long base = it.first; base <= n;) {
            exp += n / base;
            if(base <= n / it.first) {
                base *= it.first;
            }
            else {
                break;
            }
        }

        ans = min(ans,1LL * exp / it.second);
    }

    cout << ans;

    return 0;
}
