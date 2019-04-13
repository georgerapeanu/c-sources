#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("retentie.in","r");
FILE *g = fopen("retentie.out","w");

const int NMAX = 100;

int n,p;
vector<pair<int,int> > segm;

int best[NMAX + 5][NMAX + 5];
long long dp[NMAX + 5][NMAX + 5];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        int k;
        fscanf(f,"%d",&k);

        segm.clear();

        for(int j = 1;j <= k;j++){
            int x,y;
            fscanf(f,"%d %d",&x,&y);
            segm.push_back({x,y});
        }

        sort(segm.begin(),segm.end());

        int l = 1;

        for(int j = 1;j < (int)segm.size();j++){
            if(segm[l - 1].second + 1 >= segm[j].first){
                segm[l - 1].second = max(segm[l - 1].second,segm[j].second);
            }
            else{
                segm[l] = segm[j];
                l++;
            }
        }

        segm.resize(l);

        for(int j = 0;j < l;j++){
            int cost = 0;
            best[i][0] = max(best[i][0],segm[j].second - segm[j].first + 1);
            for(int k = j + 1;k < l;k++){
                cost += segm[k].first - segm[k - 1].second - 1;
                if(cost > NMAX){
                    break;
                }
                best[i][cost] = max(best[i][cost],segm[k].second - segm[j].first + 1);
            }
        }

        for(int j = 1;j <= NMAX;j++){
            best[i][j] = max(best[i][j],best[i][j - 1] + 1);
        }
    }

    fscanf(f,"%d",&p);

    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= p;j++){
            for(int l = 0;l <= j;l++){
                dp[i][j] = max(dp[i][j],dp[i - 1][j - l] + best[i][l]);
            }
        }
    }

    fprintf(g,"%lld",dp[n][p]);

    fclose(f);
    fclose(g);
    return 0;
}
