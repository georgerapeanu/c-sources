#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> elements;

int tests;
int n,m,k;

string s[105];
string t[105];

int main() {

    for(char i = 'a'; i <= 'z'; i++) {
        elements.push_back(i);
    }

    for(char i = 'A'; i <= 'Z'; i++) {
        elements.push_back(i);
    }

    for(char i = '0'; i <= '9'; i++) {
        elements.push_back(i);
    }

    cin >> tests;

    while(tests--) {
        cin >> n >> m >> k;

        for(int i = 0; i < n; i++) {
            cin >> s[i];
            t[i] = "";
            t[i].resize(m);
        }

        vector<pair<int,int> > order;

        int total = 0;

        for(int i = 0; i < n; i++) {
            for(int j = (i % 2 == 0 ? 0:m - 1); 0 <= j && j < m; j += (i % 2 == 0 ? 1:-1)) {
                order.push_back({i,j});
                total += (s[i][j] == 'R');
            }
        }

        int bucket = total / k + 1;
        int cnt = total % k;
        int id = 0;
        int how_many = 0;
        for(int i = 0; i < (int)order.size(); i++) {
            if(cnt == 0) {
                bucket--;
                cnt--;
            }
            how_many += (s[order[i].first][order[i].second] == 'R');
            if(how_many > bucket) {
                how_many -= bucket;
                id++;
                cnt--;
            }
            t[order[i].first][order[i].second] = elements[id];
        }

        for(int i = 0; i < n; i++) {
            cout << t[i] << "\n";
        }
    }


    return 0;
}
