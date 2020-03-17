///start 12:01
///finish 12:27
///final check 12:28
///submited 100
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("bibel.in","r");
FILE *g = fopen("bibel.out","w");

const int NMAX = 17;
const long long inf = 2e14;

int t;

pair<int,int> old_p[NMAX + 5];
pair<int,int> new_p[NMAX + 5];
int old_len,new_len;

long long tmp[NMAX + 5];
int biti[NMAX + 5],len_biti;
long long dp[1 << NMAX][NMAX + 1];

inline long long dist(const pair<int,int> &a,const pair<int,int> &b){
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

int main(){

    old_p[old_len = 1] = {0,0};
    dp[1][1] = 0;

    while(true){
        fscanf(f,"%d",&t);

        if(t == 0){
            new_len++;
            fscanf(f,"%d %d",&new_p[new_len].first,&new_p[new_len].second);
        }
        else if(t == 1){

            for(int i = 1;i <= old_len;i++){
                tmp[i] = dp[(1 << old_len) - 1][i];
            }

            for(int conf = 0;conf < (1 << new_len);conf++){
                for(int i = 1;i <= new_len;i++){
                    dp[conf][i] = inf;
                }
            }

            for(int i = 1;i <= old_len;i++){
                for(int j = 1;j <= new_len;j++){
                    dp[1 << (j - 1)][j] = min(dp[1 << (j - 1)][j],tmp[i] + dist(old_p[i],new_p[j]));
                }
            }

            for(int conf = 0;conf < (1 << new_len);conf++){
                len_biti = 0;
                for(int i = 1;i <= new_len;i++){
                    if((conf >> (i - 1)) & 1){
                        biti[++len_biti] = i;
                    }
                }

                for(int i = 1;i <= len_biti;i++){
                    for(int j = 1;j <= len_biti;j++){
                        if(i != j){
                            dp[conf][biti[i]] = min(dp[conf][biti[i]],dp[conf ^ (1 << (biti[i] - 1))][biti[j]] + dist(new_p[biti[i]],new_p[biti[j]]));
                        }
                    }
                }
            }

            long long ans = inf;

            for(int i = 1;i <= new_len;i++){
                ans = min(ans,dp[(1 << (new_len)) - 1][i]);
            }

            fprintf(g,"%lld\n",ans);

            memcpy(old_p,new_p,sizeof(new_p));
            memset(new_p,0,sizeof(new_p));
            old_len = new_len;
            new_len = 0;
        }
        else{
            break ;
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
