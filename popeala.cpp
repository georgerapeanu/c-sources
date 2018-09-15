#include <cstdio>
#include <algorithm>
#include <deque>
 
using namespace std;
 
const int TMAX = 2e4;
const int NMAX = 50;
const int SMAX = 50;
const int INF = (1 << 29);
 
FILE *f = stdin;
FILE *g = stdout;
 
int t,n,s;
 
int points[TMAX + 5];
int preffix_sum[TMAX + 5];
 
char results[NMAX + 5][TMAX + 5];
int valid_from[NMAX + 5][TMAX + 5];
 
int dp[SMAX + 5][TMAX + 5];
 
int ant[NMAX + 5];
int nxt[NMAX + 5];
 
int st[NMAX + 5];
int dr[NMAX + 5];
deque< pair<int,int> > segment[NMAX + 5];
 
int main(){
 
    fscanf(f,"%d %d %d\n",&n,&t,&s);
 
    for(int i = 1;i <= t;i++){
        fscanf(f,"%d",&points[i]);
        preffix_sum[i] = preffix_sum[i - 1] + points[i];
    }
     
    fscanf(f,"\n");
 
    for(int i = 1;i <= n;i++){
        fgets(results[i] + 1,TMAX + 5,f);
    }
 
    for(int i = 1;i <= n;i++){
        valid_from[i][0] = 1;
        for(int j = 1;j <= t;j++){
            valid_from[i][j] = (results[i][j] == '1' ? valid_from[i][j - 1]:j + 1);
        }
    }
 
    for(int j = 1;j <= t;j++){
        dp[0][j] = INF;
    }
     
    for(int i = 1;i <= s;i++){
 
        for(int j = 0;j <= n;j++){
            nxt[j] = j + 1;
            ant[j] = j - 1;
            st[j] = 1;
            dr[j] = 1;
            segment[j].clear(); 
        }
 
        ant[0] = n;
        nxt[n] = 0;
         
        dp[i][0] = INF;
         
        for(int j = 1;j <= t;j++){
            for(int k = 1;k <= n;k++){
                if(valid_from[k][j] != valid_from[k][j - 1]){
                    nxt[ant[k]] = nxt[k];
                    ant[nxt[k]] = ant[k];
 
                    int head = ant[0];
 
                    nxt[k] = nxt[head];
                    ant[k] = head;
 
                    nxt[ant[k]] = k;
                    ant[nxt[k]] = k;
                }
            }
             
            if(j < i){
                dp[i][j] = INF;
                continue;
            }
                                       
            dp[i][j] = INF;
             
            for(int seg = n,nod = ant[0];seg >= 0;seg--,nod = ant[nod]){
				
				int left = valid_from[nod][j];
				int right = (nxt[nod] == 0 ? j + 1:valid_from[nxt[nod]][j]);
				
                while(dr[seg] < right){
                    int cost = dp[i - 1][dr[seg] - 1] - preffix_sum[dr[seg] - 1] * seg;
                    while(segment[seg].size() && segment[seg].back().second >= cost){
                        segment[seg].pop_back();
                    }
                    segment[seg].push_back({dr[seg],cost});
                    dr[seg]++;
                }
                 
                while(st[seg] < left){
                    while(segment[seg].size() && segment[seg].front().first <= st[seg]){
                        segment[seg].pop_front();
                    }
                    st[seg]++;
                }
                 
                if(segment[seg].size()){
                    dp[i][j] = min(dp[i][j],segment[seg].front().second + preffix_sum[j] * seg);
                }
            }
        }   
        fprintf(g,"%d\n",dp[i][t]);
    }
     
    return 0;
}