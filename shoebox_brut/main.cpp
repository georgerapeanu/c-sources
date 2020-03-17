#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("shoebox.in","r");
FILE *g = fopen("shoebox.ok","w");

const int NMAX = 1e3;
const int LMAX = 1e3;

int t;
int n;
pair<int,int> v[NMAX + 5];

int dp[NMAX + 5];
int ends[NMAX + 5],len;

int main(){

    fscanf(f,"%d",&t);
    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&v[i].first,&v[i].second);
        if(v[i].first > v[i].second){
            swap(v[i].first,v[i].second);
        }
    }

    sort(v + 1,v + 1 + n);

    if(t == 1){
        int ans = 0;
        for(int i = 1;i <= n;i++){
            for(int j = 1;j < i;j++){
                if(v[j].second <= v[i].second){
                    dp[i] = max(dp[i],dp[j]);
                }
            }
            dp[i]++;
            ans = max(ans,dp[i]);
        }
        fprintf(g,"%d\n",ans);
    }
    else{
        for(int i = 1;i <= n;i++){
            int bst_idx = -1;
            for(int j = 1;j <= len;j++){
                if(ends[j] <= v[i].second && (bst_idx == -1 || ends[bst_idx] < ends[j])){
                    bst_idx = j;
                }
            }
            if(bst_idx == -1){
                ends[++len] = v[i].second;
            }
            else{
                ends[bst_idx] = v[i].second;
            }
        }
        fprintf(g,"%d\n",len);
    }


    fclose(f);
    fclose(g);

    return 0;
}
