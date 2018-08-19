//This is getting accepted!
// I HATE BUG
// God Of The Bugs
// 12/11/2016
#include<bits/stdc++.h>

using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FI first
#define SE second
#define pb push_back
#define mp make_pair
#define ll long long
#define sz(a) ((int)(a).size())
#define __builtin_popcount __builtin_popcounll
#define ld long double

typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, pii> ppi;

const double PI = acos(0) * 2;
const double EPS = 1e-8;
const ll MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const int oo = 1e9;
const double foo = 1e30;

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcounll(s);}
template<class T> T sqr(T x) { return x * x; }

inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

double dp[11000][1001];
int k, q, p[MAXN];

int main() {

	cin >> k >> q;

	dp[0][0] = 1;
	for (int i=1; i<=10000; i++) {
		for (int j=1; j<=k; j++) {
			double p = (double) (k - j + 1) / (double) k;
//			if (i == 1 && j == 1) cout << p << endl;
			dp[i][j] += dp[i - 1][j - 1] * p;
			p = (double) j / (double) k;
			dp[i][j] += dp[i - 1][j] * p;
		}
	}
	cout<<dp[4][3];
//	cout << printf("%.12lf", dp[10000][1000]) << endl;
//	for (int i=1; i<=2000; i++) if (dp[i][k] >= 0.1) {
//		cout << "here";
//	}

	for (int i=0; i<q; i++) {
		scanf("%d", &p[i]);
		double tar = p[i] / 2000.;
		for (int i=0; i<=10000; i++) {
			if (dp[i][k] + EPS > tar) {
				printf("%d\n", k);
				break;
			}
		}
	}




}

