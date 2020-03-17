#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
int ferikire[NMAX + 5];

pair<int,int> edges[NMAX + 5];

vector<int> graph[NMAX + 5];
int fst[NMAX + 5];
int snd[NMAX + 5];
int euler_len;
int lant_father[NMAX + 5];
int lvl[NMAX + 5];
int when[NMAX + 5];

void predfs(int nod,int tata) {
    lvl[nod] = 1 + lvl[tata];
    fst[nod] = ++euler_len;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod);
    }
    snd[nod] = euler_len;
}

int aint[2 * NMAX + 5];

void update(int pos,const int &val) {
    for(aint[pos += n] = val; pos > 1; pos >>= 1) {
        aint[pos >> 1] = (when[aint[pos ^ 1]] > when[aint[pos]] ? aint[pos ^ 1] : aint[pos]);
    }
}

int query(int l,int r) {
    l += n;
    r += n + 1;

    int ans = 0;

    for(; l < r; l >>= 1,r >>= 1) {
        if(l & 1) {
            ans = (when[ans] > when[aint[l]] ? ans:aint[l]);
            l++;
        }
        if(r & 1) {
            ans = (when[ans] > when[aint[r - 1]] ? ans:aint[r - 1]);
            r--;
        }
    }

    return ans;
}

int aib[NMAX + 5];

void aib_update(int pos,int val) {
    for(; pos <= NMAX; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int aib_query(int pos) {
    int ans = 0;

    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }

    return ans;
}

int main() {

    scanf("%d",&n);

    vector<int> tmp;

    for(int i = 1; i <= n; i++) {
        scanf("%d",&ferikire[i]);
        tmp.push_back(ferikire[i]);
    }

    sort(tmp.begin(),tmp.end());
    tmp.resize(unique(tmp.begin(),tmp.end()) - tmp.begin());

    for(int i = 1; i <= n; i++) {
        ferikire[i] = lower_bound(tmp.begin(),tmp.end(),ferikire[i]) - tmp.begin() + 1;
    }

    when[1] = 1;
    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
        edges[i] = {x,y};
        when[y] = i + 1;
    }

    predfs(1,0);

    update(fst[1],1);
    lant_father[1] = 0;

    for(int i = 1; i < n; i++) {
        int nod = edges[i].first;
        long long ans = 0;
        vector<pair<int,int> > to_clear;
        while(nod != 0) {
            int _lant = query(fst[nod],snd[nod]);
            ans += 1LL * (lvl[nod] - lvl[lant_father[_lant]]) * aib_query(ferikire[_lant] - 1);
            aib_update(ferikire[_lant],lvl[nod] - lvl[lant_father[_lant]]);
            to_clear.push_back({ferikire[_lant],lvl[lant_father[_lant]] - lvl[nod]});
            int lst_nod = nod;
            nod = lant_father[_lant];
            lant_father[_lant] = lst_nod;
        }
        update(fst[edges[i].second],edges[i].second);
        lant_father[edges[i].second] = 0;
        for(auto it:to_clear) {
            aib_update(it.first,it.second);
        }
        printf("%lld\n",ans);
    }



    return 0;
}
