#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n,p;
pair<int,int> t[NMAX + 5];
long long ans[NMAX + 5];

int main() {

    scanf("%d %d",&n,&p);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&t[i].first);
        t[i].second = i;
    }

    sort(t + 1,t + 1 + n);

    set<int> boiler;
    set<int> waiting;
    queue<int> ord;

    boiler.insert(t[1].second);
    ord.push(t[1].second);

    long long lst_t = t[1].first;
    int lst = 1;

    while((lst < n) || boiler.empty() == false || waiting.empty() == false) {
        while(lst < n && t[lst + 1].first < lst_t + p) {
            lst++;
            if(boiler.empty() == true || boiler.lower_bound(t[lst].second) == boiler.begin()) {
                boiler.insert(t[lst].second);
                ord.push(t[lst].second);
            }
            else {
                waiting.insert(t[lst].second);
            }
        }

        if(boiler.empty() == false) {
            lst_t += p;
            boiler.erase(ord.front());
            ans[ord.front()] = lst_t;
            ord.pop();

            while(lst < n && t[lst + 1].first == lst_t) {
                lst++;
                waiting.insert(t[lst].second);
            }

            while(waiting.empty() == false && (boiler.empty() == true || (*boiler.begin() > *waiting.begin()))) {
                boiler.insert(*waiting.begin());
                ord.push(*waiting.begin());
                waiting.erase(waiting.begin());
            }
        }
        else {
            lst++;
            lst_t = t[lst].first;
            boiler.insert(t[lst].second);
            ord.push(t[lst].second);
        }
    }

    for(int i = 1; i <= n; i++) {
        printf("%lld ",ans[i]);
    }

    return 0;
}
