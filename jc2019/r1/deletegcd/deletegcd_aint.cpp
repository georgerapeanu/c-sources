#include <bits/stdc++.h>

using namespace std;

const size_t LEN = 1 << 20;

char buff[LEN];
size_t buff_index = LEN - 1;

int u32() {
  int answer = 0;

  while (buff[buff_index] < '0' || buff[buff_index] > '9') {
    if (++buff_index >= LEN) {
      fread(buff, 1, LEN, stdin);
      buff_index = 0;
    }
  }

  while ('0' <= buff[buff_index] && buff[buff_index] <= '9') {
    answer = answer * 10 + buff[buff_index] - '0';
    if (++buff_index >= LEN) {
      fread(buff, 1, LEN, stdin);
      buff_index = 0;
    }
  }

  return answer;
}

long long gcd(long long a, long long b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
  if (a == 0 && b == 0) {
    return 0;
  }
  return 1LL * a * b / gcd(a, b);
}

struct node_t {
  int gcd_all;
  long long lcm_without_one;

  node_t(const int &value) {
    gcd_all = value;
    lcm_without_one = 0;
  }

  node_t() { node_t(0); }

  node_t operator+(const node_t &other) const {
    node_t answer(0);
    answer.gcd_all = gcd(this->gcd_all, other.gcd_all);
    answer.lcm_without_one = lcm(gcd(this->gcd_all, other.lcm_without_one),
                                 gcd(this->lcm_without_one, other.gcd_all));
    return answer;
  }
};

class FastSegmentTree {
  int n;
  vector<node_t> aint;

public:
  FastSegmentTree(vector<int> &values) {
    this->n = values.size();
    this->aint = vector<node_t>(2 * n);
    for (int i = 0; i < n; i++) {
      this->aint[i + n] = node_t(values[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
      this->aint[i] = this->aint[i * 2] + this->aint[i * 2 + 1];
    }
  }

  bool query(int l, int r) {
    node_t answer = node_t(0);
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        answer = answer + aint[l++];
      }
      if (r & 1) {
        answer = answer + aint[--r];
      }
    }

    return answer.lcm_without_one != 1;
  }
};

int main() {
  freopen("deletegcd.in", "r", stdin);
  freopen("deletegcd.out", "w", stdout);
  int n = u32();
  int q = u32();

  vector<int> values(n);
  for (auto &it : values) {
    it = u32();
  }

  auto aint = FastSegmentTree(values);

  while (q--) {
    int l = u32();
    int r = u32();

    l--;
    putc('0' + aint.query(l, r), stdout);
  }

  return 0;
}
