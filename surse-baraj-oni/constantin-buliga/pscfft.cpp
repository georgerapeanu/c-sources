#include <fstream>
#include <vector>

using namespace std;

const int MAXN = 500000;

int v[1 + MAXN];

vector<int> Get(int k, int s) {
    vector<int> answer;
    if (!k) {
        answer.push_back(0);
        return answer;
    }
    for (int i = 0; i < s; i++) {
        vector<int> temp = Get(k - 1, s);
        for (auto &it : temp)
            answer.push_back((it + i) % s);
    }
    return answer;
}

int FindIn(vector<int> &w, int n) {
    for (int i = 0; i + n - 1 < w.size(); i++) {
        bool bad = false;
        for (int j = 1; j <= n; j++)
            if (v[j] != w[i + j - 1]) {
                bad = true;
                break;
            }
        if (!bad)
            return i;
    }
    return -1;
}

int main() {
    freopen("pscfft.in", "r", stdin);
    freopen("pscfft.out", "w", stdout);
    int tests;
    scanf("%d", &tests);
    for (int test = 1; test <= tests; test++) {
        int n, s;
        scanf("%d%d", &n, &s);
        for (int i = 1; i <= n; i++)
            scanf("%d", &v[i]);
        if (s == 1) {
            if (n == 1 && v[1] == 0)
                printf("0\n");
            else
                printf("-1\n");
            continue;
        }
        vector<int> w;
        w.push_back(0);
        int x = FindIn(w, n);
        while (x == -1 && 1LL * w.size() * s <= MAXN) {
            vector<int> t;
            for (int i = 0; i < s; i++)
                for (auto &it : w)
                    t.push_back((it + i) % s);
            w = t;
            x = FindIn(w, n);
        }
        printf("%d\n", x);
    }
    return 0;
}
