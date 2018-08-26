//ceva mai bun (sper)
#include <bits/stdc++.h>
 
using namespace std;
 
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
 
class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;
 
    void write_ch(char ch) {
        if (sp == 262144) {
            fwrite(buff, 1, 262144, fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }
 
 
public:
  OutParser(const char* name) {
    fout = fopen(name, "w");
    buff = new char[262144]();
    sp = 0;
  }
  ~OutParser() {
    fwrite(buff, 1, sp, fout);
    fclose(fout);
  }
 
  OutParser& operator << (int vu32) {
    if (vu32 < 0) {
      write_ch('-');
      vu32 = -vu32;
    }
    if (vu32 <= 9) {
      write_ch(vu32 + '0');
    } else {
      (*this) << (vu32 / 10);
      write_ch(vu32 % 10 + '0');
    }
    return *this;
  }
 
  OutParser& operator << (long long vu64) {
    if (vu64 <= 9) {
      write_ch(vu64 + '0');
    } else {
      (*this) << (vu64 / 10);
      write_ch(vu64 % 10 + '0');
    }
    return *this;
  }
 
  OutParser& operator << (char ch) {
    write_ch(ch);
    return *this;
  }
  OutParser& operator << (const char *ch) {
    while (*ch) {
      write_ch(*ch);
      ++ch;
    }
    return *this;
  }
};
char s[320005];
int sp[320005];
long long sum1[320005], sum2[320005];
long long p1[320005], p2[320005];
 
int bs1(int st, int dr, int val) {
  int last = 0;
  while (st <= dr) {
    int med = (st + dr) / 2;
    if (p1[med] < val) {
      last = med;
      st = med + 1;
    } else {
      dr = med - 1;
    }
  }
  return last;
}
 
int bs2(int st, int dr, int val) {
  int last = dr + 1;
  while (st <= dr) {
    int med = (st + dr) / 2;
    if (p1[med] > val) {
      last = med;
      dr = med - 1;
    } else {
      st = med + 1;
    }
  }
  return last;
}
 
int bs3(int st, int dr, int val) {
  int last = dr + 1;
  while (st <= dr) {
    int med = (st + dr) / 2;
    if (p2[med] >= val) {
      last = med;
      dr = med - 1;
    } else {
      st = med + 1;
    }
  }
  return last;
}
 
long long f(int k, int l, int r, int n, int a, int b, int c, int z) {
  long long s1 = sum1[a] - sum1[a - k];
  int t = z - k;
  long long s2 = sum1[t + b - 1] - sum1[b - 1];
  long long s3 = sum2[c + k - 1] - sum2[c - 1];
  long long s4 = sum2[c + z - 1] - sum2[c + k - 1];
  return s2 + s3 - s1 - s4;
}
 
long long cauta(int l, int r, int a, int b, int n, int x, int y, int z, int t) {
  while (r - l >= 3) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    long long f1 = f(m1, a, b, n, x, y, z, t);
    long long f2 = f(m2, a, b, n, x, y, z, t);
    if (f1 > f2)
      l = m1;
    else
      r = m2;
  }
  long long ans = f(l, a, b, n, x, y, z, t);
  if (l + 1 <= r)
    ans = min(ans, f(l + 1, a, b, n, x, y, z, t));
  if (l + 2 <= r)
    ans = min(ans, f(l + 2, a, b, n, x, y, z, t));
  return ans;
}
 
 
 
int main() {
  InParser fin("copii3.in");
  OutParser fout("copii3.ok");
  //freopen("copii3.in", "r", stdin);
  //freopen("copii3.out", "w", stdout);
 
  int n, q, k1 = 0, k2 = 0;
  fin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    fin >> s[i];
    if (s[i] == '0') {
      sp[i] = 1;
      p1[++k1] = i;
      sum1[k1] = sum1[k1 - 1] + i;
    }
    else {
      p2[++k2] = i;
      sum2[k2] = sum2[k2 - 1] + i;
    }
    sp[i] += sp[i - 1];
  }
  for (int i = 1; i <= q; ++i) {
    int l, r;
    fin >> l >> r;
    int x = sp[l - 1];
    int y = sp[n] - sp[r];
    int z = r - l + 1 - (sp[r] - sp[l - 1]);
    if (x + y < z) {
      fout << -1 << '\n';
      continue;
    }
    int a = bs1(1, k1, l);
    int b = bs2(1, k1, r);
    int c = bs3(1, k2, l);
    long long ans = cauta(max(0, z - y), min(x, z), l, r, n, a, b, c, z);
    fout << ans << '\n';
  }
 
  return 0;
}