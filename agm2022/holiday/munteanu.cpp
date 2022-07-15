#include <bits/stdc++.h>

using namespace std;

vector <int> graph[100005];
vector <pair <int, pair <int, int>>> edges;
int dp[20][100005];
int height[100005];

void initDp(int node, int father, int h) {
    height[node] = h;
    dp[0][node] = father;
    for (auto x : graph[node]) {
        if (x == father) continue;
        initDp(x, node, h + 1);
    }
}

void updateDp(int n) {
    for (int p = 1; p < 20; ++p) {
        for (int i = 1; i <= n; ++i) {
            dp[p][i] = dp[p - 1][dp[p - 1][i]];
        }
    }
}

int findLca(int x, int y) {
    if (height[x] < height[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if ((1 << i) <= height[x] - height[y]) {
            x = dp[i][x];
        }
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (dp[i][x] != dp[i][y]) {
            x = dp[i][x];
            y = dp[i][y];
        }
    }
    return dp[0][x];
}

int father[100005], heightDisojoint[100005], sizeDisjoint[100005];

int getFather(int x) {
    int boss = x;
    while (boss != father[boss]) boss = father[boss];
    while (x != boss) {
        int nextX = father[x];
        father[x] = boss;
        x = nextX;
    }
    return boss;
}

void join(int x, int y) {
    int fatherX = getFather(x);
    int fatherY = getFather(y);
    if (fatherX == fatherY) return;
    if (heightDisojoint[fatherX] > heightDisojoint[fatherY]) {
        father[fatherY] = fatherX;
        sizeDisjoint[fatherX] += sizeDisjoint[fatherY];
    } else if (heightDisojoint[fatherX] < heightDisojoint[fatherY]) {
        father[fatherX] = fatherY;
        sizeDisjoint[fatherY] += sizeDisjoint[fatherX];
    } else {
        heightDisojoint[fatherX] += 1;
        father[fatherY] = fatherX;
        sizeDisjoint[fatherX] += sizeDisjoint[fatherY];
    }
}

bool areTogether(int x, int y) {
    return getFather(x) == getFather(y);
}

int getOnPath(int x, int y) {
    int lca = findLca(x, y);
    if (areTogether(x, lca)) {
        int current = y;
        for (int i = 19; i >= 0; --i) {
            if ((1 << i) <= height[current] - height[lca] && !areTogether(x, dp[i][current])) {
                current = dp[i][current];
            }
        }
        //cout << "currently " <<  x << " " <<  y << " " << current << " " << areTogether(x, current) << endl;
        return - 2 * height[lca] + height[x] + height[current] + areTogether(x, current);
    } else {
        int current = x;
        for (int i = 19; i >= 0; --i) {
            if (areTogether(x, dp[i][current])) {
                current = dp[i][current];
            }
        }
        return height[x] - height[current] + 1;
    }
}

bool cmp(pair <pair <int, int>, pair <int, pair <int, int>>> A, pair <pair <int, int>, pair <int, pair <int, int>>> B) {
    return A.first.second < B.first.second;
}

vector <pair <pair <int, int>, pair <int, pair <int, int>>>> queries;
void pushPower(int added, vector <pair <int, pair <int, int>>> &edgesOrder, int n) {
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        heightDisojoint[i] = 1;
        sizeDisjoint[i] = 1;
    }
    for (auto &x : queries) {
        x.first.second += added;
    }
    int currentNodeIndex = 0;
    for (auto &x : queries) {
        while (currentNodeIndex < edgesOrder.size() && edgesOrder[currentNodeIndex].first <= x.first.second) {
            join(edgesOrder[currentNodeIndex].second.first, edgesOrder[currentNodeIndex].second.second);
            currentNodeIndex += 1;
        }
        //cout << x.first.second << " " << sizeDisjoint[getFather(x.second.second.first)] << " " << getOnPath(x.second.second.first, x.second.second.second) << endl; 
        if (sizeDisjoint[getFather(x.second.second.first)] - getOnPath(x.second.second.first, x.second.second.second) < x.second.first) {
            continue;
        }
        x.first.second -= added;
    }
    sort(queries.begin(), queries.end(), cmp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int x, y, cost;
        cin >> x >> y >> cost;
        edges.push_back({cost, {x, y}});
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    initDp(1, 0, 1);
    updateDp(n);
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= q; ++i) {
        int x, y, k;
        cin >> x >> y >> k;
        queries.push_back({{i, -1}, {k, {x, y}}});
    }
    for (int power = 29; power >= 0; --power) {
        pushPower((1 << power), edges, n);
    }
    sort(queries.begin(), queries.end());
    for (auto x : queries) {
        cout << (x.first.second == (1 << 30) - 2 ? -1:x.first.second + 1) << ' ';
    }
    return 0;
}

