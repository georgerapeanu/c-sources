#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int t;

    cin >> t;

    while(t--) {
        int n,k;
        string s;
        cin >> n >> k;
        cin >> s;
        vector<pair<int,int> > ans;

        for(int i = 0; i < 2 * k - 2; i ++) {
            int id = -1;
            for(int j = i; j < (int)s.size() && id == -1; j++) {
                if((i % 2 == 0 && s[j] == '(') || (i % 2 == 1 && s[j] == ')')) {
                    id = j;
                }
            }
            if(id > i) {
                reverse(s.begin() + i,s.begin() + id + 1);
                ans.push_back({i,id});
            }
        }
        for(int i = 2 * k - 2; i < (int)s.size(); i++) {
            int id = -1;
            for(int j = i; j < (int)s.size() && id == -1; j++) {
                if(s[j] == '(') {
                    id = j;
                }
            }
            if(id > i) {
                reverse(s.begin() + i,s.begin() + id + 1);
                ans.push_back({i,id});
            }
        }

        printf("%d\n",ans.size());
        for(auto it:ans) {
            printf("%d %d\n",it.first + 1,it.second + 1);
        }
    }

    return 0;
}
