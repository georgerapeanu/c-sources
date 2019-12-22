#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int a[1005];
vector<pair<int,int> > states;

int lst = 0;
pair<int,int> ant[1000 * 1000 + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    states.push_back({n + 1,0});

    for(int i = 1; i <= n; i++) {
        int cnt0 = n + 1 - a[i];
        int cnt1 = a[i];
        sort(states.begin(),states.end());

        vector<pair<int,int> > n_states = {};

        for(auto it:states) {
            if(it.first == 1) {
                n_states.push_back({1,++lst});
                if(cnt1 > cnt0) {
                    ant[lst] = {1,it.second};
                    cnt1--;
                }
                else {
                    ant[lst] = {0,it.second};
                    cnt0--;
                }
            }
            else {
                if(cnt0 == 0) {
                    n_states.push_back({it.first,++lst});
                    ant[lst] = {1,it.second};
                    cnt1 -= it.first;
                }
                else if(cnt1 == 0) {
                    n_states.push_back({it.first,++lst});
                    ant[lst] = {0,it.second};
                    cnt0 -= it.first;
                }
                else {
                    n_states.push_back({min(it.first - 1,cnt0),++lst});
                    ant[lst] = {0,it.second};
                    int tmp = min(it.first - 1,cnt0);
                    cnt0 -= min(it.first - 1,cnt0);
                    n_states.push_back({it.first - tmp,++lst});
                    ant[lst] = {1,it.second};
                    cnt1 -= it.first - tmp;
                }
            }
        }
        states = n_states;
    }

    printf("%d\n",n + 1);

    for(auto it:states) {
        int state = it.second;
        vector<int> tmp;
        while(state) {
            tmp.push_back(ant[state].first);
            state = ant[state].second;
        }
        reverse(tmp.begin(),tmp.end());
        for(auto it:tmp) {
            printf("%d",it);
        }
        printf("\n");
    }

    return 0;
}
