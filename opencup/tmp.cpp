#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

char s[MAXN];

int main() {

    int n;
    while (scanf("%d ", &n) != EOF) {
        scanf("%s", s + 1);
        set<int>s0;
        set<int>s2;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == '0')
                s0.insert(i);
            else if (s[i] == '2')
                s2.insert(i);
        }
        vector<pair<int, int> >s20;
        for (auto it:s2) {
            set<int>::iterator it1 = s0.lower_bound(it);
            if (it1 == s0.end())
                break;
            s20.push_back({it, (*it1)});
            s0.erase(it1);
        }
        
        sort(s20.begin(),s20.end(),[&](pair<int,int> &a,pair<int,int> &b){
                    return a.second < b.second;
                });

        set<pair<int,int> > active;

        int ans = 0;

        for(int i = (int)s20.size() - 1;i >= 0;i--){
            if(active.lower_bound({s20[i].second,0}) != active.end()){
                ans++;
                active.erase(active.lower_bound({s20[i].second,0}));
            }
            else{
                active.insert(s20[i]);
            }
        }
        printf("%d\n",ans);
  }

  return 0;
}

