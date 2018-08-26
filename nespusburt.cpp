#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX_N = 100000;
 
class InParser {
private:
  FILE *fin;
  char *buff;
  int sp;
 
  char read_ch() {
    ++sp;
    if (sp == 262144) {
      sp = 0;
      fread(buff, 1, 262144, fin);
    }
    return buff[sp];
  }
 
public:
  InParser(const char* nume) {
    fin = fopen(nume, "r");
    buff = new char[262144]();
    sp = 262143;
  }
  InParser& operator >> (char &n) {
    char c;
    while (!isdigit(c = read_ch()) && c != '-');
    n = c;
    return *this;
  }
  InParser& operator >> (int &n) {
    char c;
    while (!isdigit(c = read_ch()) && c != '-');
    int sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }
 
  InParser& operator >> (long long &n) {
    char c;
    n = 0;
    while (!isdigit(c = read_ch()) && c != '-');
    long long sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }
};
 
 
int a[MAX_N + 5], b[MAX_N + 5], c[MAX_N + 5];
vector<int>G[MAX_N + 5];
int f[MAX_N + 5], lt[MAX_N + 5];
int viz[MAX_N + 5];
int val[2 * MAX_N + 5];
int ind1[MAX_N + 5];
int pas;
int aux;
int q1[MAX_N + 5], q2[MAX_N + 5], q[MAX_N + 5];
int st, st1, st2;
int dr, dr1, dr2;
 
inline bool get(int a, int b) {
  pas++;
  viz[a] = viz[b] = pas;
  st1 = 0;
  dr1 = 0;
  st2 = 0;
  dr2 = 0;
  q1[0] = a;
  q2[0] = b;
  while (st1 <= dr1 && st2 <= dr2) {
    int n1 = q1[st1];
    int n2 = q2[st2];
 
    bool ok = 0;
    for (int i = f[n1]; i <= lt[n1]; ++i) {
      int it = G[n1][i];
      if (viz[it] != pas) {
        ok = 1;
        viz[it] = pas;
        q1[++dr1] = it;
        break;
      }
    }
    if (!ok)
      st1++;
 
    ok = 0;
    for (int i = f[n2]; i <= lt[n2]; ++i) {
      int it = G[n2][i];
      if (viz[it] != pas) {
        ok = 1;
        viz[it] = pas;
        q2[++dr2] = it;
        break;
      }
    }
    if (!ok)
      st2++;
  }
 
  if (st1 > dr1)
    return 1;
  return 0;
 
}
 
inline void ceva(int n1, int n2) {
  pas++;
  int s1 = 0;
  aux++;
  st = 0;
  q[0] = n1;
  dr = 0;
  while (st <= dr) {
    n1 = q[st];
    st++;
    viz[n1] = pas;
    ind1[n1] = aux;
    s1++;
    for (int i = f[n1]; i <= lt[n1]; ++i) {
      int it = G[n1][i];
      if (viz[it] != pas)
        q[++dr] = it;
    }
  }
  val[aux] = s1;
  val[ind1[n2]] -= s1;
}
 
inline void altceva(int n1, int n2) {
  pas++;
  st = dr = 0;
  q[0] = n1;
  while (st <= dr) {
    n1 = q[st];
    st++;
    viz[n1] = pas;
    ind1[n1] = ind1[n2];
    val[ind1[n2]]++;
    for (int i = f[n1]; i <= lt[n1]; ++i) {
      int it = G[n1][i];
      if (viz[it] != pas)
        q[++dr] = it;
    }
  }
}
 
inline int addEdge(int e) {
  int x = (val[ind1[a[e]]] < val[ind1[b[e]]]);
  if (x) {
    altceva(a[e], b[e]);
  } else {
    altceva(b[e], a[e]);
  }
  f[a[e]]--;
  f[b[e]]--;
  return val[ind1[a[e]]];
}
 
inline int removeEdge(int e, int k, int sz) {
  lt[a[e]]--;
  lt[b[e]]--;
  int x = get(a[e], b[e]);
  int ll = val[ind1[a[e]]];
  if (x) {
    ceva(a[e], b[e]);
  } else {
    ceva(b[e], a[e]);
  }
  if (ll >= k && sz >= k && (val[ind1[a[e]]] < k && val[ind1[b[e]]] < k))
    return -1;
  return sz;
}
 
int main() {
  InParser fin("nespus.in");
  freopen("nespus.ok", "w", stdout);
 
  int n, k;
  fin >> n >> k;
  for (int i = 1; i < n; ++i) {
    fin >> a[i] >> b[i] >> c[i];
    ind1[i] = i;
    val[i] = 1;
    G[a[i]].push_back(b[i]);
    G[b[i]].push_back(a[i]);
 
  }
  for (int i = 1; i <= n; ++i) {
    lt[i] = G[i].size() - 1;
    f[i] = 1 + lt[i];
  }
  val[n] = 1;
  ind1[n] = n;
  aux = n;
 
  int r = n - 1, l = n - 1, ans = 1000000000;
  int sz = -1;
  while (r >= 1) {
    while (l >= 1 && sz < k) {
      sz = addEdge(l);
      l--;
    }
    if (l == 0 && sz < k)
      break;
    ans = min(ans, c[r] - c[l + 1]);
    sz = removeEdge(r, k, sz);
    r--;
  }
 
  printf("%d\n", ans);
 
  return 0;
}