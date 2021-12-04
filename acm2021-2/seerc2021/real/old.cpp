#include <bits/stdc++.h>

using namespace std;

//Link:   https://github.com/georgerapeanu/kactl/blob/main/content/contest/template.cpp
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int inf = 1e9;

/*Link: https://github.com/georgerapeanu/kactl/blob/main/content/data-structures/FenwickTree.h
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FT {
	vector<ll> s;
	FT(int n) : s(n, -inf) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = max(s[pos], dif);
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = -inf;
		for (; pos > 0; pos &= pos - 1) res = max(res, s[pos-1]);
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};


/* Link: https://github.com/georgerapeanu/kactl/blob/main/content/data-structures/FenwickTree2d.h
**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = -inf;
		for (; x; x &= x - 1)
			sum = max(sum,ft[x-1].query(ind(x-1, y)));
		return sum;
	}
};

int main(){
    
  int n, m;
  vector<int> a;
  vector<int> b;

  scanf("%d %d",&n,&m);

  a = vector<int>(n,0);
  b = vector<int>(m,0);

  for(auto &it:a){
    scanf("%d",&it);
  }

  for(auto &it:b){
    scanf("%d",&it);
  }

  a.push_back(inf + 1);
  n++;

  vector<pair<int,int> > together;

  for(int i = 0;i < n;i++){
    together.push_back({a[i],i});
  }

  for(int i = 0;i < m;i++){
    together.push_back({b[i],-1});
  }

  sort(together.begin(),together.end());

  int cnt_a = 0;
  int cnt_b = 0;

  vector<int> coef(n,0);
  for(auto it:together){
    if(it.second == -1){
      cnt_b++;
    }else{
      cnt_a++;
      a[it.second] = cnt_a;
      coef[it.second] = cnt_b - it.second;
    }
  }

  FT2 aib(n + 1);

  aib.fakeUpdate(0, 1);
  for(int i = 0;i < n;i++){
    aib.fakeUpdate(a[i], coef[i]);
  }

  aib.init();
  aib.update(0,1,0);
  vector<int> dp(n + 1, 0);

/*
  for(int i = 0;i < n;i++){
    printf("debug %d %d\n",a[i], coef[i]);
  }
*/
  for(int i = 0;i < n;i++){
    dp[i + 1] = aib.query(a[i], coef[i] + 2);
  //  printf("query on %d %d is %d\n",a[i],coef[i] + 2,dp[i + 1]);
    if(dp[i + 1] == -inf){
      continue;
    }
    dp[i + 1]++;
    aib.update(a[i], coef[i], dp[i + 1]);
  //  printf("update %d %d with %d\n",a[i],coef[i],dp[i + 1]);
  }

/*
  for(auto it:dp){
    printf("debug %d\n",it);
  }
*/

  
  if(dp[n] < 0){
    printf("-1\n");
    return 0;
  }

  printf("%d\n", n - dp[n]);

    return 0;
}

