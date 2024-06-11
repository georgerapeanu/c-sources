#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 1e6 + 1;
const int MOD = 1e9 + 7;

int add(int a, int b) {
  a += b;
  if(a >= MOD) {
    a -= MOD;
  }
  return a;
}

int sub(int a, int b) {
  a -= b;
  if(a < 0) {
    a += MOD;
  }
  return a;
}

int mult(int a, int b) {
  return 1LL * a * b % MOD;
}

typedef unsigned long long ull;
typedef long long ll;

ull modmul(ull a, ull b, ull mod) {
	ll ret = a * b - mod * ull(1.L / mod * a * b);
	return ret + mod * (ret < 0) - mod * (ret >= (ll)mod);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool IsPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return n == 2 || n == 3; 
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n - 1), d = n >> s;
  for (auto a : A) {   // ^ count trailing zeroes
    ull p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a, b, k;
  cin >> a >> b >> k;

  std::vector <long long> prime;
  bool is_composite[MAX_SIZE];

  auto sieve =  [&](int n) {
    std::fill (is_composite, is_composite + n, false);
    for (int i = 2; i < n; ++i) {
      if (!is_composite[i]) prime.push_back (i);
      for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
        is_composite[i * prime[j]] = true;
        if (i % prime[j] == 0) break;
      }
    }
  };
  sieve(MAX_SIZE);

  long long total_productish = 1;
  vector<int> fr(prime.size(), 0);
  vector<long long> leftovers;
  for(int i = 1; i <= k; i++) {
    long long n;
    cin >> n;
    
    if(1LL * a * b / n >= total_productish) {
      total_productish *= n;
    } else {
      total_productish = 1LL * a * b + 1;
    }
    
    if(n < MAX_SIZE || !IsPrime(n)) {
      for(int j = 0; j < (int)prime.size() && prime[j] <= n ; j++) {
        while(n % prime[j] == 0) {
          n /= prime[j];
          fr[j]++;
        }
      }
    }
    
    if(n > 1) {
      leftovers.push_back(n);
    }
  }

  int count_leftover = 0;
  int last_leftover = -1;

  for(auto it: leftovers) {
    if(last_leftover != it) {
      if(count_leftover > 0) {
        prime.push_back(last_leftover);
        fr.push_back(count_leftover);
      }
      count_leftover = 0;
      last_leftover = it;
    }
    count_leftover += 1;
  }
  prime.push_back(last_leftover);
  fr.push_back(count_leftover);

  int count_divs = 1;
  int answer = 0;
  int sum_divs_positive = 1;

  for(int i = 0; i < (int)prime.size(); i++) {
    count_divs = mult(count_divs, add(1, fr[i]));
    int current_sum = 0;
    int last_div = 1;
    for(int j = 0; j <= fr[i]; j++) {
      current_sum = add(current_sum, last_div);
      last_div = mult(last_div, prime[i] % MOD);
    }
    sum_divs_positive = mult(sum_divs_positive, current_sum);
  }
    
  answer = add(sum_divs_positive, mult(a, count_divs));
  if(total_productish <= 1LL * a * b) {
    vector<long long> divs;
    vector<pair<int, long long> > current;
    current.push_back({0, 1});
    while(!current.empty()) {
      auto tmp = current.back();
      current.pop_back();
      if(tmp.first >= (int)prime.size()) {
        divs.push_back(tmp.second);
      } else {
        for(int i = 0; i <= fr[tmp.first]; i++) {
          current.push_back({tmp.first + 1, tmp.second});
          tmp.second *= prime[tmp.first];
        }
      }
    }
    for(auto d: divs) {
      long long other_d = total_productish / d;
      if(-d + a > 0 && -other_d + b > 0) {
        answer = add(answer, sub((a % MOD), (d % MOD))); 
      }
    }
  }
  cout << answer << "\n";

  return 0;
}

