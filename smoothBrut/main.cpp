#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s[100005];
bool f[30];
int f1[30];

int main() {
  freopen("smooth2.in", "r", stdin);
  freopen("smooth2.out", "w", stdout);

  int n;
  scanf("%s", s + 1);
  n = strlen(s + 1);
  int dif = 0;
  for (int i = 1; i <= n; ++i)
    if (f[s[i] - 'a'] == 0) {
      dif++;
      f[s[i] - 'a'] = 1;
    }
  int ans = n;
  memset(f, 0, sizeof(f));
  for (int l = 1; l <= min(n, 26); ++l) {
    int nr = n / l;
    for (int i = 1; i <= nr; ++i) {
      for (int j = l * (i - 1) + 1; j <= l * i; ++j) {
        if (f[s[j] - 'a'] == 0) {
          f[s[j] - 'a'] = 1;
          f1[s[j] - 'a']++;
        }
      }
      memset(f, 0, sizeof(f));
    }
    for (int i = l * nr + 1; i <= n; ++i)
      f[s[i] - 'a'] = 1;
    for (int j = 0; j < 26; ++j)
      f1[j] += f[j];
    memset(f, 0, sizeof(f));
    sort(f1, f1 + 26);
    int s = 0;
    for (int j = 25; j >= 25 - l + 1; --j)
      s += f1[j];
    ans = min(ans, n - s);
    memset(f1, 0, sizeof(f1));
  }

  printf("%d\n", ans);

  return 0;
}

