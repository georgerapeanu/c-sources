#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("pedefe.in","r");
FILE *g = fopen("pedefe.out","w");

const int NMAX = 500;
const int MMAX = 500;
const int PMAX = 100;
const int MOD = 666013;

int n,m,p;
int s1[NMAX + 5];
int s2[MMAX + 5];
int s3[PMAX + 5];

pair<int,int> pos[NMAX * MMAX + 5];

int dp[2][NMAX + 5][MMAX + 5];
int aib[2][NMAX + 5][MMAX + 5];

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

void update(int l,int j,int k,int val){
    j++;
    k++;
    for(int x = j;x <= n + 1;x += (-x) & x){
        for(int y = k;y <= m + 1;y += (-y) & y){
            aib[l][x][y] = add(aib[l][x][y],val);
        }
    }
}

int query(int l,int j,int k){
    int ans = 0;
    j++;
    k++;
    for(int x = j;x > 0;x -= (-x) & x){
        for(int y = k;y > 0;y -= (-y) & y){
            ans = add(aib[l][x][y],ans);
        }
    }
    return ans;
}

int main(){
    
    fscanf(f,"%d %d %d",&n,&m,&p);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&s1[i]);
    }

    for(int i = 1;i <= m;i++){
        fscanf(f,"%d",&s2[i]);
    }
    
    for(int i = 1;i <= p;i++){
        fscanf(f,"%d",&s3[i]);
    }

    int len = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(s1[i] == s2[j]){
                pos[++len] = {i,j};
            }
        }
    }

    sort(pos + 1,pos + 1 + len,
        [&](pair<int,int> &a,pair<int,int> &b){
            if(s1[a.first] != s1[b.first]){
                return s1[a.first] < s1[b.first];
            }
            if(a.first != b.first){
                return a.first < b.first;
            }
            return a.second < b.second;
        });

    dp[0][0][0] = 1;

    for(int i = 1,l = 1;i <= p;i++,l ^= 1){
        for(int j = 0;j <= n + 1;j++){
            for(int k = 0;k <= m + 1;k++){
                dp[l][j][k] = 0;
            }
        }
        for(int wh = 1;wh <= len;wh++){
            int j = pos[wh].first;
            int k = pos[wh].second;
            for(int x = j - 1;x >= 0;x--){
                for(int y = k - 1;y >= 0;y--){
                    dp[l][j][k] = add(dp[l][x][y],dp[l][j][k]);
                }
            }
            if(s3[i] == s1[j]){
                for(int x = j - 1;x >= 0;x--){
                    for(int y = k - 1;y >= 0;y--){
                        dp[l][j][k] = add(dp[l ^ 1][x][y],dp[l][j][k]);
                    }
                }
            }
        }
    }

    int ans = 0;

    for(int j = 0;j <= n;j++){
        for(int k = 0;k <= m;k++){
            ans = add(ans,dp[p & 1][j][k]);
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
