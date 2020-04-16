#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int MOD = 998244353;

class ModularInt {
public:
    int val;

    ModularInt() {
        val = 0;
    }

    ModularInt(int val) {
        this->val = val % MOD;
    }

    ModularInt(long long val) {
        this->val = val % MOD;
    }

    ModularInt operator + (const ModularInt &other)const {
        ModularInt ans(this->val + other.val);
        if(ans.val >= MOD) {
            ans.val -= MOD;
        }
        return ans;
    }

    ModularInt operator - (const ModularInt &other)const {
        ModularInt ans(this->val - other.val);
        if(ans.val < 0) {
            ans.val += MOD;
        }
        return ans;
    }

    ModularInt operator * (const ModularInt &other)const {
        return ModularInt(1LL * this->val * other.val % MOD);
    }
};

int n;
vector<int> graph[NMAX + 5];
ModularInt dp[NMAX + 5][3];///(node,state) state=0 => node has no incident edge from its subtree, state=1 => node has at least one incident edge and is not in the independence set,state = 2 same but it is in the set
ModularInt tmp[3];

void dfs(int nod,int tata) {
    dp[nod][0] = ModularInt(1);

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);

        tmp[0] = dp[nod][0] * (dp[it][0] + dp[it][1] + dp[it][2]);
        tmp[1] = (dp[nod][0] * (dp[it][0] * ModularInt(2) + dp[it][1] + dp[it][2]) + ModularInt(1) * dp[nod][1] * (dp[it][0] * ModularInt(3) + dp[it][1] * ModularInt(2) + dp[it][2] * ModularInt(2)));
        tmp[2] = (dp[nod][0] * (dp[it][0] + dp[it][1]) + ModularInt(1) * dp[nod][2] * (dp[it][0] * ModularInt(2) + dp[it][1] * ModularInt(2) + dp[it][2]));

        dp[nod][0] = tmp[0];
        dp[nod][1] = tmp[1];
        dp[nod][2] = tmp[2];
    }

}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    ModularInt ans = (dp[1][0] + dp[1][1] + dp[1][2]);

    ans = ans - ModularInt(1);

    printf("%d\n",ans.val);

    return 0;
}
