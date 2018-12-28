#include <iostream>
#include <iomanip>

using namespace std;

const int MOD = 998244353;
const int NMAX = 2e5;

int n;
int v[NMAX + 5];
int cnt2[NMAX + 5];

int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }
    return p;
}

int fact(int n){
    int ans = 1;
    for(int i = 1;i <= n;i++){
        ans = 1LL * ans * i % MOD;
    }
    return ans;
}

int aib[NMAX + 5];

void update(int pos,int val){
    for(;pos <= NMAX;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int sum = 0;
    for(;pos;pos -= (-pos) & pos){
        sum += aib[pos];
    }
    return sum;
}

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    
    cin >> n; 
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        cin >> v[i];
        cnt += (v[i] == -1);
        if(v[i] != -1){
            cnt2[v[i]] = 1;
        }
    }

    for(int i = 1;i <= n;i++){
        cnt2[i] = cnt2[i - 1] + !cnt2[i];
    }

    int ans = 0;
    int sum = 0;
    int icnt = lgpow(cnt,MOD - 2);
    double tmp_ans = 0;
    int st = 0;

    for(int i = 1;i <= n && cnt;i++){
        if(v[i] == -1){
           st++;
        }
        else{
            tmp_ans += double(cnt - st) / cnt * cnt2[v[i]];
            tmp_ans += double(st) / cnt * (cnt - cnt2[v[i]]);
            ans = (ans + 1LL * (cnt - st) * (1LL * cnt2[v[i]] * icnt % MOD)) % MOD;
            ans = (ans + 1LL * (st) * (1LL * (cnt - cnt2[v[i]]) * icnt % MOD)) % MOD;
        }
    }
   
    int iv = 0;

    for(int i = n;i;i--){
        if(v[i] != -1){
            iv = (iv + query(v[i])) % MOD;
            update(v[i],1);
        }
    }

  // cout << fixed << setprecision(4) << tmp_ans << "\n";
    ans = (ans + iv) % MOD;
    tmp_ans += iv;
  // cout << fixed << setprecision(4) << tmp_ans << "\n";
    ans = (ans + 1LL * (1LL * cnt * (cnt - 1) % MOD) * lgpow(4,MOD - 2)) % MOD;
  // cout << fixed << setprecision(4) << tmp_ans << "\n";
    tmp_ans += cnt * double(cnt - 1) / 4;
    cout << ans;

  // cout << fixed << setprecision(4) << tmp_ans << "\n";
  //  cout << cnt2[2]; 
   return 0;
}
