#include <bits/stdc++.h>

using namespace std;

int n,k;
string s;

vector<vector<int>> paralel;

int main() {

    cin >> n >> k;

    cin >> s;


    int mi = 0;
    int ma = 0;
    int pref = 0;
    int len = 0;

    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] == 'R') {
            pref += 1;
            len = max(0,len - 1);
        }
        else {
            mi = max(mi,pref + len);
            ma += pref;
            len++;
        }
    }

    if(mi > k || ma < k) {
        printf("-1\n");
        return 0;
    }

    while(k) {
        vector<int> tmp;
        for(int i = 1; i < (int)s.size(); i++) {
            if(s[i] == 'L' && s[i - 1] == 'R') {
                tmp.push_back(i);
                i++;
            }
        }

        if(ma - (int)tmp.size() >= k - 1) {
            k--;
            ma -= (int)tmp.size();
            printf("%d ",(int)tmp.size());
            for(auto it:tmp) {
                printf("%d ",it);
                swap(s[it - 1],s[it]);
            }
            printf("\n");
        }
        else {
            int x = ma - k + 1;
            printf("%d ",x);
            for(int i = 0; i < x; i++) {
                printf("%d ",tmp[i]);
                swap(s[tmp[i]],s[tmp[i] - 1]);

            }
            ma -= x;
            k--;
            printf("\n");
            break;
        }
    }

    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] == 'L') {
            int pos = i;
            while(pos && s[pos - 1] == 'R') {
                swap(s[pos],s[pos - 1]);
                printf("1 %d\n",pos);;
                pos--;
            }
        }
    }

    return 0;
}
