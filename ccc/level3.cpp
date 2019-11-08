#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int VMAX = 1e9;

int n,m;
int a[NMAX + 5][NMAX + 5];
int col[NMAX + 5][NMAX + 5];

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

int border[NMAX + 5];
bool is_border[NMAX + 5][NMAX + 5];
vector<pair<int,int> > comp[NMAX + 5];
pair<long double,long double> capital[NMAX + 5];

long double get_dist(pair<long double,long double> a,pair<long double,long double> b) {
    return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}

int main() {

    scanf("%d %d",&n,&m);

    int mi = VMAX + 5;
    int ma = -VMAX - 5;
    long double avg = 0;

    int ma_country = -VMAX - 5;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d",&a[i][j]);
            scanf("%d",&col[i][j]);
            mi = min(mi,a[i][j]);
            ma = max(ma,a[i][j]);
            avg += a[i][j];
            ma_country = max(ma_country,col[i][j]);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            comp[col[i][j]].push_back({i,j});
            capital[col[i][j]].first += i;
            capital[col[i][j]].second += j;
            for(int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];
                if(x < 0 || x >= n || y < 0 || y >= m || col[i][j] != col[x][y]) {
                    border[col[i][j]]++;
                    is_border[i][j] = true;
                    break;
                }
            }
        }
    }

    for(int i = 0; i <= ma_country; i++) {
        capital[i].first /= double(comp[i].size());
        capital[i].second /= double(comp[i].size());
        capital[i].first = int(capital[i].first);
        capital[i].second = int(capital[i].second);

        pair<int,int> best_cap = comp[i].back();
        long double dist = 1e9;

        for(auto it:comp[i]) {
            if(is_border[it.first][it.second]) {
                continue;
            }
            if(dist > get_dist(it,capital[i])) {
                dist = get_dist(it,capital[i]);
                best_cap = it;
            }
        }
        capital[i] = best_cap;
        printf("%d %d\n",best_cap.second,best_cap.first);
    }

    return 0;
}
