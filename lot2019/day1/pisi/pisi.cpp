#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class AIB {
    vector<int> aib;

public:

    AIB(int n) {
        aib = vector<int>(n + 1,-1);
    }

    void update(int pos,int val) {
        pos++;
        for(; pos; pos -= (-pos) & pos) {
            aib[pos] = max(aib[pos],val);
        }
    }

    int query(int pos) {
        pos++;
        int ans = -1;
        for(; pos < (int)aib.size(); pos += (-pos) & pos) {
            ans = max(ans,aib[pos]);
        }
        return ans;
    }
};

vector<int> rank_cats(vector<int> p,vector<int> f,vector<int> d) {
    vector<int> pos_p(p.size(),0);
    vector<int> pos_f(f.size(),0);
    vector<int> pos_d(d.size(),0);
    vector<int> ans(p.size(),0);
    for(int i = 0; i < (int)p.size(); i++) {
        ans[i] = i;
        p[i]--;
        f[i]--;
        d[i]--;
        pos_p[p[i]] = i;
        pos_f[f[i]] = i;
        pos_d[d[i]] = i;
    }

    sort(ans.begin(),ans.end(),[&](int a,int b) {
        int cnt = 0;
        cnt += (pos_p[a] < pos_p[b]);
        cnt += (pos_f[a] < pos_f[b]);
        cnt += (pos_d[a] < pos_d[b]);
        return cnt >= 2;
    });

    AIB pf(p.size());
    AIB fd(f.size());
    AIB dp(d.size());

    for(auto it:ans) {

        if(pf.query(pos_p[it] + 1) > pos_f[it]) {
            return vector<int>();
        }
        if(fd.query(pos_f[it] + 1) > pos_d[it]) {
            return vector<int>();
        }
        if(dp.query(pos_d[it] + 1) > pos_p[it]) {
            return vector<int>();
        }


        pf.update(pos_p[it],pos_f[it]);
        fd.update(pos_f[it],pos_d[it]);
        dp.update(pos_d[it],pos_p[it]);
    }

    for(auto &it:ans) {
        it++;
    }
    return ans;

}

int main() {


    int n;
    vector<int> p;
    vector<int> f;
    vector<int> d;
    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        p.push_back(val);
    }

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        f.push_back(val);
    }

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        d.push_back(val);
    }

    vector<int> ans = rank_cats(p,f,d);

    for(auto it:ans) {
        printf("%d ",it);
    }
    if(ans.empty()) {
        printf("NO SOLUTION");
    }
    printf("\n");

    return 0;
}
