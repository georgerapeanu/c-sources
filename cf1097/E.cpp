#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n;
int v[NMAX + 5];
int l[NMAX + 5],len;
int cnt[NMAX + 5];
int ant[NMAX + 5];
int ant2[NMAX + 5];
bool aval[NMAX + 5];

vector< vector<int> > solve() {
    vector< vector<int> > ans;

    memset(aval,0,sizeof(aval));
    int lim = n;

    while(1) {
        int k = 0;
        for(int i = 1; 1; i++) {
            if(1LL * i * (i + 1) / 2 > lim) {
                k = i;
                break;
            }
        }

        len = 0;
        for(int i = 1; i <= n; i++) {
            if(!aval[i]) {
                int st = 0;
                int dr = len + 1;
                while(dr - st > 1) {
                    int mid = (st + dr) / 2;
                    if(v[l[mid]] <= v[i]) {
                        st = mid;
                    }
                    else {
                        dr = mid;
                    }
                }
                if(st == len) {
                    len++;
                    l[len] = 0;
                }
                ant2[i] = l[st + 1];
                l[st + 1] = i;
                ant[i] = l[st];
            }
        }

        if(len == 0) {
            break;
        }

        if(len < k) {
            for(int i = 1; i <= len; i++) {
                vector<int> seq;
                int id = l[i];
                for(; id; id = ant2[id]) {
                    seq.push_back(v[id]);
                    aval[id] = true;
                    lim--;
                }
                reverse(seq.begin(),seq.end());
                ans.push_back(seq);
            }
            break;
        }
        else {
            vector<int> seq;
            int id = l[len];
            for(; id; id = ant[id]) {
                seq.push_back(v[id]);
                aval[id] = true;
                lim--;
            }
            reverse(seq.begin(),seq.end());
            ans.push_back(seq);
        }
    }
    return ans;
}

int main() {
    int t;
    scanf("%d\n",&t);

    while(t--) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i++) {
            scanf("%d",&v[i]);
        }

        vector< vector<int> > tmp = solve();

        printf("%d\n",tmp.size());
        for(auto seq:tmp) {
            printf("%d ",seq.size());
            for(auto it:seq) {
                printf("%d ",it);
            }
            printf("\n");
        }
    }
    return 0;
}
