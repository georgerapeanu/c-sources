#include <bits/stdc++.h>

using namespace std;

set<int> active;
set<int> cant;
int cnt;

int n;

vector<int> events;

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);

        if(val < 0) {
            val *= -1;
            if(active.count(val) == 0) {
                printf("-1\n");
                return 0;
            }
            active.erase(val);
        }
        else {
            if(cant.count(val)) {
                printf("-1\n");
                return 0;
            }
            cant.insert(val);
            active.insert(val);
        }
        cnt++;
        if(active.empty()) {
            events.push_back(cnt);
            cnt = 0;
            cant.clear();
        }
    }

    if(active.empty() == false) {
        printf("-1\n");
        return 0;
    }

    printf("%d\n",events.size());
    for(auto it:events) {
        printf("%d\n",it);
    }

    return 0;
}
