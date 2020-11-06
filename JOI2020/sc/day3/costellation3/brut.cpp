    #include<cstdio>
    #include<algorithm>
    #include<vector>
    #define N_ 401000
    #define SZ 262144
    #define pii pair<int,int>
    using namespace std;
    int n, H[N_], m, IT[SZ + SZ], cnt;
    vector<pii>G[N_];
    void Put(int a, int b) {
    	a += SZ;
    	IT[a] = b;
    	while (a != 1) {
    		a >>= 1;
    		IT[a] = max(IT[a * 2], IT[a * 2 + 1]);
    	}
    }
    pii GetMax(int b, int e) {
    	b += SZ, e += SZ;
    	int pv = -1, Mx = -1;
    	while (b <= e) {
    		if (Mx < IT[b])Mx = IT[b], pv = b;
    		if (Mx < IT[e])Mx = IT[e], pv = e;
    		b = (b + 1) >> 1, e = (e - 1) >> 1;
    	}
    	while (pv < SZ) {
    		pv *= 2;
    		if (IT[pv] != Mx)pv++;
    	}
    	return { Mx,pv - SZ };
    }
    int Left[N_], Right[N_], par[N_], TT[SZ + SZ];
    int Ed[N_];
    vector<pii>Z[N_];
    void Put(int b, int e, int c) {
    	b += SZ, e += SZ;
    	while (b <= e) {
    		TT[b] = TT[e] = c;
    		b = (b + 1) >> 1, e = (e - 1) >> 1;
    	}
    }
    int Get(int a) {
    	int r = 0;
    	a += SZ;
    	while (a) {
    		r = max(r, TT[a]);
    		a >>= 1;
    	}
    	return r;
    }
    void Do(int b, int e, int d) {
    	cnt++;
    	int cur = cnt;
    	pii tp = GetMax(b, e);
    	int mid = tp.second, h = tp.first;
    	Put(h + 1, d, cur);
    	for (auto &t : G[mid]) {
    		Z[Get(t.first)].push_back({ cur, t.second });
    	}
    	if (b == e) {
    		Ed[cur] = cnt;
    		return;
    	}
    	if (b < mid) {
    		Left[cur] = cnt + 1;
    		par[cnt + 1] = cur;
    		Do(b, mid - 1, h);
    	}
    	if (mid < e) {
    		Right[cur] = cnt + 1;
    		par[cnt + 1] = cur;
    		Do(mid + 1, e, h);
    	}
    	Ed[cur] = cnt;
    }
    long long D[N_], BIT[N_];
    void Add2(int a, long long b) {
    	while (a <= cnt) {
    		BIT[a] += b;
    		a += (a&-a);
    	}
    }
    long long Sum(int a) {
    	long long r = 0;
    	while (a) {
    		r += BIT[a];
    		a -= (a&-a);
    	}
    	return r;
    }
    void Add(int b, int e, long long t) {
    	Add2(b, t);
    	Add2(e + 1, -t);
    }
    void Go(int a) {
    	int l = Left[a], r = Right[a];
    	if (l) {
    		Go(l);
    	}
    	if (r) {
    		Go(r);
    	}
    	if (l&&r) {
    		Add(l, Ed[l], D[r]);
    		Add(r, Ed[r], D[l]);
    	}
    	Add(a, a, D[r] + D[l]);
    	D[a] = D[l] + D[r];
    	for (auto &t : Z[a]) {
    		D[a] = max(D[a], Sum(t.first) + t.second);
    	}
    }
    int main() {
    	int i;
    	scanf("%d", &n);
    	for (i = 1; i <= n; i++) {
    		scanf("%d", &H[i]);
    		Put(i, H[i]);
    	}
    	scanf("%d", &m);
    	long long s = 0;
    	for (i = 1; i <= m; i++) {
    		int x, y, c;
    		scanf("%d%d%d", &x, &y, &c);
    		G[x].push_back({ y,c });
    		s += c;
    	}
    	Do(1, n, n);
    	Go(1);
    	printf("%lld\n", s - D[1]);
    }
