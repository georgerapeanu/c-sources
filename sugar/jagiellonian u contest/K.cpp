#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

const int NMAX = 1e5;

int t,n;
vector<int> graph[NMAX + 5];
int weight[NMAX + 5];
bool in_centr[NMAX + 5];
vector<int> root_cnt,centroid_cnt;
deque<int> same_lvl[NMAX + 5];
int lvl[NMAX + 5];

void calc_weights(int nod,int tata) {
    weight[nod] = 1;

    for(auto it:graph[nod]) {
        if(it != tata && !in_centr[it]) {
            calc_weights(it,nod);
            weight[nod] += weight[it];
        }
    }
}

void get_cnt_on_lvl(int nod,int tata,vector<int> &cnt) {
    lvl[nod] = 1 + lvl[tata];

    while((int)cnt.size() <= lvl[nod] - 1) {
        cnt.push_back(0);
    }

    cnt[lvl[nod] - 1]++;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }

        if(!in_centr[it]) {
            get_cnt_on_lvl(it,nod,cnt);
        }
    }
}

void dfs_smen(int nod,int tata,const vector<int> &root_cnt,const vector<int> &centroid_cnt,long long &ans,const int centroid) {
    lvl[nod] = 1 + lvl[tata];
    same_lvl[nod].clear();
    for(auto it:graph[nod]) {
        if(it != tata && !in_centr[it]) {
            dfs_smen(it,nod,root_cnt,centroid_cnt,ans,centroid);
            if(same_lvl[it].size() > same_lvl[nod].size()) {
                swap(same_lvl[nod],same_lvl[it]);
            }
        }
    }

    for(auto it:graph[nod]) {
        if(it != tata && !in_centr[it]) {
            for(int i = 0; i < (int)same_lvl[it].size(); i++) {
                int lvl_int = (i + 1) - (lvl[nod] - lvl[centroid]);
                int coef = 0;
                if(lvl_int > 0) {
                    coef = centroid_cnt[lvl_int] - root_cnt[lvl_int - 1];
                }
                else if(lvl_int == 0) {
                    coef = 1;
                }
                ans += 1LL * same_lvl[nod][i] * same_lvl[it][i] * coef;
                same_lvl[nod][i] += same_lvl[it][i];
            }
        }
    }
    same_lvl[nod].push_front(1);
}

vector<int> tmp_cnt;

void dfs(int nod,long long &ans) {
    calc_weights(nod,0);
    int centroid = nod,father = 0;
    while(1) {
        int big_child = -1;
        for(auto it:graph[centroid]) {
            if(it != father && !in_centr[it] && weight[it] * 2  >= weight[nod]) {
                big_child = it;
                break;
            }
        }

        if(big_child == -1) {
            break;
        }

        father = centroid;
        centroid = big_child;
    }

    in_centr[centroid] = true;

    for(auto it:graph[centroid]) {
        if(!in_centr[it]) {
            dfs(it,ans);
        }
    }

    in_centr[centroid] = false;
    centroid_cnt.clear();
    get_cnt_on_lvl(centroid,0,centroid_cnt);
    in_centr[centroid] = true;

    tmp_cnt = vector<int>(centroid_cnt.size(),0);
    for(auto it:graph[centroid]) {
        if(!in_centr[it]) {
            root_cnt.clear();
            get_cnt_on_lvl(it,0,root_cnt);
            dfs_smen(it,centroid,root_cnt,centroid_cnt,ans,centroid);
            for(int i = 0; i < (int)root_cnt.size(); i++) {
                ans += 1LL * tmp_cnt[i] * root_cnt[i] * (centroid_cnt[i + 1] - tmp_cnt[i] - root_cnt[i]);
                tmp_cnt[i] += root_cnt[i];
            }
        }
    }

    in_centr[centroid] = false;
}

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            graph[i].clear();
        }

        for(int i = 1; i < n; i++) {
            int x,y;
            scanf("%d %d",&x,&y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        long long ans = 0;
        dfs(1,ans);
        printf("%lld\n",ans);
    }
    return 0;
}
