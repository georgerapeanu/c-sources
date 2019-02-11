#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200000;
const int MOD = 1000000007;
const int MAXLOG = 29;

vector<int> g[1 + MAXN];
int value[1 + MAXN], order[1 + MAXN];
int power2[1 + MAXN], dad[1 + MAXN], bits[1 + MAXN][1 + MAXLOG], weight[1 + MAXN], height[1 + MAXN];
int total[1 + MAXLOG];
bool active[1 + MAXN];

void Add(int &x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
}

void Subtract(int &x, int y) {
    x -= y;
    if (x < 0)
        x += MOD;
}

void Precompute(int n) {
    power2[0] = 1;
    for (int i = 1; i <= n; i++) {
        power2[i] = power2[i - 1];
        Add(power2[i], power2[i - 1]);
        dad[i] = i;
        weight[i] = 1;
        height[i] = 1;
        for (int j = 0; j <= MAXLOG; j++)
            if (value[i] & (1 << j))
                bits[i][j]++;
    }
}

inline bool Compare(const int &a, const int &b) {
    return value[a] > value[b];
}

int Count(int have1, int have0, int parity) {
    int answer = 0;
    if (parity)
        if (have1)
            answer = power2[have1 - 1 + have0];
        else
            answer = 0;
    else {
        if (have1)
            answer = power2[have1 - 1 + have0];
        else
            answer = power2[have0];
        Subtract(answer, 1);
    }
    return answer;
}

int FindDad(int node) {
    if (dad[node] == node)
        return node;
    return dad[node] = FindDad(dad[node]);
}

void Join(int a, int b) {
    a = FindDad(a);
    b = FindDad(b);
    if (height[a] < height[b]) {
        dad[a] = b;
        weight[b] += weight[a];
        for (int i = 0; i <= MAXLOG; i++)
            bits[b][i] += bits[a][i];
    }
    else {
        if (height[a] == height[b])
            height[a]++;
        dad[b] = a;
        weight[a] += weight[b];
        for (int i = 0; i <= MAXLOG; i++)
            bits[a][i] += bits[b][i];
    }
}

int Activate(int node) {
    int answer = 0;
    active[node] = true;
    for (int i = 0; i <= MAXLOG; i++)
        total[i] = 0;
    for (auto &it : g[node])
        if (active[it]) {
            int root = FindDad(it);
            for (int j = 0; j <= MAXLOG; j++)
                Subtract(answer, (1LL * (1 << j) * Count(bits[root][j], weight[root] - bits[root][j], 1 ^ ((value[node] >> j) & 1))) % MOD);
            Join(it, node);
        }
    int root = FindDad(node);
    for (int j = 0; j <= MAXLOG; j++)
        Add(answer, (1LL * (1 << j) * Count(bits[root][j], weight[root] - bits[root][j], 1 ^ ((value[node] >> j) & 1))) % MOD);
    return answer;
}

int main() {
    freopen("countfefete.in", "r", stdin);
    freopen("countfefete.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
        order[i] = i;
    }
    Precompute(n);
    sort(order + 1, order + n + 1, Compare);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int answer = 0;
    for (int i = 1; i <= n; i++)
        Add(answer, Activate(order[i]));
    printf("%d\n", answer);
    return 0;
}
