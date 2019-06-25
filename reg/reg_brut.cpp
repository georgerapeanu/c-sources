#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

FILE *f = fopen("reg.in","r");
FILE *g = fopen("reg.ok","w");

const int NMAX = 2e6;
const int VMAX = 4e6;

int t,n;
int a,b,c,k;
int x[NMAX + 5];
int nxt[NMAX + 5];
int last_pos[VMAX + 5];
bool in[VMAX + 5];

int main(){

    x[1] = 1;

    fscanf(f,"%d",&t);
    
    while(t--){
        memset(last_pos,0,sizeof(last_pos));
        memset(in,0,sizeof(in));
        
        fscanf(f,"%d %d %d %d %d",&a,&b,&c,&n,&k);
        for(int i = 2;i <= n;i++){
            x[i] = (1LL * x[i - 1] * a + 1LL * b * i) % c;
        }
        
        for(int i = n;i;i--){
            nxt[i] = (last_pos[x[i]] == 0 ? (1 << 30):last_pos[x[i]]);
            last_pos[x[i]] = i;
        }
        
        memset(last_pos,0,sizeof(last_pos));///used to see if we used this
        map<int,int> pq;

        int ans = n;
        
        for(int i = 1;i <= n;i++){
            if(in[x[i]] == true){
                pair<int,int> tmp = {nxt[i],pq[i]};
                pq.erase(i);
                pq[tmp.first] = tmp.second;
                continue;
            }
            else if(last_pos[x[i]] == 0){
                last_pos[x[i]] = i;
                if((int)pq.size() < k){
                    pq[nxt[i]] = x[i];
                    in[x[i]] = true;
                }
                else{
                    in[pq.rbegin()->second] = false;
                    pq.erase(pq.find(pq.rbegin()->first));
                    pq[nxt[i]] = x[i];
                    in[x[i]] = true;
                }
            }
            else{
                ans = i - 1;
                break;
            }
        }
        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
