#include <cstdio>
#include <vector>
#include <algorithm>
  
using namespace std;
   
FILE *f = fopen("armate.in","r");
FILE *g = fopen("armate.out","w");
   
const int NMAX = 400;
const int QMAX = 800;
const int VMAX = 80000;
   
int n,q;
   
vector< pair<int,int> > query[NMAX + 5];
int v[NMAX + 5];
int ans[QMAX + 5];
bool precalc[NMAX + 5][VMAX + 5];
int smallest_bigger[NMAX + 5][VMAX + 5];
  
inline int modul(int x){
    return x < 0 ? -x:x;
}
   
void solve(int l,int r){
    if(l == r){
        for(auto it:query[l]){
            if(it.first == l){
                ans[it.second] = v[it.first];
            }
        }
        return ;
    }
    int mid = (l + r) / 2;
    solve(l,mid);
    solve(mid + 1,r);
       
    for(int i = l;i <= r;i++){
        for(int j = 0;j <= VMAX;j++){
            precalc[i][j] = 0;
            smallest_bigger[i][j] = 0;
        }
    }
   
    precalc[mid][v[mid]] = 1;
    precalc[mid + 1][v[mid + 1]] = 1;
   
    smallest_bigger[mid][VMAX] = VMAX + 1;
    smallest_bigger[mid + 1][VMAX] = VMAX + 1;
       
    for(int j = VMAX - 1;j >= 0;j--){
        smallest_bigger[mid][j] = (precalc[mid][j] ? j:smallest_bigger[mid][j + 1]);
        smallest_bigger[mid + 1][j] = (precalc[mid + 1][j] ? j:smallest_bigger[mid + 1][j + 1]);
    }
       
    for(int i = mid - 1;i >= l;i--){
        for(int j = 0;j <= VMAX;j++){
            if(!precalc[i + 1][j]){
                continue;
            }
   
            if(modul(j + v[i]) <= VMAX){
                precalc[i][modul(j + v[i])] = 1;
            }
              
            if(modul(j - v[i]) <= VMAX){
                precalc[i][modul(j - v[i])] = 1;
            }
        }
   
        smallest_bigger[i][VMAX] = (precalc[i][VMAX] ? 0:VMAX + 1);
   
        for(int j = VMAX - 1; j >= 0; j--){
            smallest_bigger[i][j] = (precalc[i][j] ? j:smallest_bigger[i][j + 1]);
        }
    }
   
    for(int i = mid + 2;i <= r;i++){
        for(int j = 0;j <= VMAX;j++){
            if(!precalc[i - 1][j]){
                continue;
            }
   
            if(modul(j + v[i]) <= VMAX){
                precalc[i][modul(j + v[i])] = 1;
            }
              
            if(modul(j - v[i]) <= VMAX){
                precalc[i][modul(j - v[i])] = 1;
            }
        }
           
        smallest_bigger[i][VMAX] = (precalc[i][VMAX] ? 0:VMAX + 1);
   
        for(int j = VMAX - 1; j >= 0; j--){
            smallest_bigger[i][j] = (precalc[i][j] ? j:smallest_bigger[i][j + 1]);
        }
    }
       
    for(int i = l; i <= mid;i++){
        for(auto it:query[i]){
            if(it.first > mid && it.first <= r){
                for(int j = 0;j <= VMAX;j++){
                    if(!precalc[i][j]){
                        continue;
                    }
   
                    if(smallest_bigger[it.first][j] != VMAX + 1){
                        ans[it.second] = min(ans[it.second],smallest_bigger[it.first][j] - j);
                    }
                }
            }
        }
    }
	
	for(int i = mid + 1; i <= r;i++){
        for(auto it:query[i]){
            if(it.first <= mid && it.first >= l){
                for(int j = 0;j <= VMAX;j++){
                    if(!precalc[i][j]){
                        continue;
                    }
   
                    if(smallest_bigger[it.first][j] != VMAX + 1){
                        ans[it.second] = min(ans[it.second],smallest_bigger[it.first][j] - j);
                    }
                }
            }
        }
    }
}
   
int main(){
   
    fscanf(f,"%d %d",&n,&q);
   
    for(int i = 1; i <= n; i++){
        fscanf(f,"%d",&v[i]);
    }
   
    for(int i = 1;i <= q;i++){
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        query[l].push_back({r,i});
        query[r].push_back({l,i});
        ans[i] = 1e9;
    }
   
    solve(1,n);
   
    for(int i = 1; i <= q;i++){
        fprintf(g,"%d\n",ans[i]);
    }
   
    fclose(f);
    fclose(g);
   
    return 0;
}