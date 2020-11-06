#include <bits/stdc++.h>

using namespace std;

struct data_t{
    int a,b;

    long long cost()const{
        long long ans = 0;
        int a = this->a;
        int b = this->b;
        ans -= (1LL * (a % b) * (a / b + 1) * (a / b + 1) + 1LL * (b - (a % b)) * (a / b) * (a / b));
        b++;
        ans += (1LL * (a % b) * (a / b + 1) * (a / b + 1) + 1LL * (b - (a % b)) * (a / b) * (a / b));
        b--;
        return ans;
    }

    bool operator < (const data_t &other)const{
        return this->cost() > other.cost();
    }
};

int main(){

    int n,k;

    cin >> n >> k;

    priority_queue<data_t> pq;

    long long ans = 0;

    for(int i = 1;i <= n;i++){
         int val;
         cin >> val;
         pq.push({val,1});
         ans += 1LL * val * val;
    }

    k -= n;

    while(k--){
        data_t tmp = pq.top();
        pq.pop();
        ans += tmp.cost();
        tmp.b++;
        pq.push(tmp);
    }

    cout << ans;

    return 0;
}
