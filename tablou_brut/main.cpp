#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream f("tablou.in");
ofstream g("tablou.ok");

const int NMAX = 3000;
const int MMAX = 3000;
const int KMAX = 1e5;

int t;
int n,m,k;

vector<vector<string> > masterpieces;
vector<long long> master_sum;
vector<string> orig;

int main(){
    orig.clear();
    masterpieces.clear();
    master_sum.clear();

    f >> n >> m;

    orig.resize(n + 1);

    for(int i = 1;i <= n;i++){
        f >> orig[i];
        orig[i] = " " + orig[i];
    }

    f >> k;

    for(int i = 1;i <= k;i++){
        int x,y,xx,yy,c;
        f >> x >> y >> xx >> yy >> c;
        masterpieces.push_back(orig);
        master_sum.push_back(0);
        for(int i = x;i <= xx;i++){
            for(int j = y;j <= yy;j++){
                (masterpieces.back())[i][j] = c + '0';
            }
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                master_sum.back() += (masterpieces.back())[i][j] - '0';
            }
        }
    }

    for(auto it:master_sum){
        g << it << "\n";
    }

    for(int i = 0;i < k;i++){
        long long cost = 0;
        for(int j = 0;j < k;j++){
            cost += 1LL * n * m * (master_sum[i] - master_sum[j]);
        }
        g << cost << "\n";
    }

    f.close();
    g.close();
    return 0;
}
