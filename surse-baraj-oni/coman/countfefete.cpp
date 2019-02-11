#include <stdio.h>
#include <vector>
#include <algorithm>
#define MAXN 200000
#define MAXB 30

const long long MOD = 1000000007LL;

std::vector <int> G[1 + MAXN];
std::vector <int> V[1 + MAXN];
int v[1 + MAXN];
int root, last;
long long tmp0[1 + MAXN][1 + MAXB];
long long tmp1[1 + MAXN][1 + MAXB];
int bad[1 + MAXN];
int w[1 + MAXN];
bool cmp(int a, int b){return v[a] < v[b];}

inline void dfs(int node, int father){
    if(bad[node]) return;
    V[root].push_back(v[node]);
    V[last].push_back(v[node]);
    for(auto y: G[node]) if(y != father && v[y] >= v[root])
        dfs(y, node);
}

inline void Combine(int ind, int val){
    for(int i = 0; i <= MAXB; i++){
        if((val & (1 << i)) == 0){
            tmp0[ind][i] *= 2;
            tmp1[ind][i] *= 2;
        }
        else
            tmp0[ind][i] = tmp1[ind][i] = tmp0[ind][i] + tmp1[ind][i];
        tmp0[ind][i] %= MOD;
        tmp1[ind][i] %= MOD;
    }
}

int main(){
    FILE*fi,*fo;
    fi = fopen("countfefete.in","r");
    fo = fopen("countfefete.out","w");

    int n;
    fscanf(fi,"%d", &n);
    for(int i = 1; i <= n; i++) fscanf(fi,"%d", &v[i]);

    for(int i = 1; i < n; i++){
        int x, y;
        fscanf(fi,"%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for(int i = 1; i <= n; i++) w[i] = i;
    std::sort(w + 1, w + n + 1, cmp);

    long long answer = 0;
    for(int Root = 1; Root <= n; Root++){
        root = w[Root];
        V[root].clear();
        for(auto y:G[root]) if(v[y] >= v[root]){
            last = y;
            V[last].clear();
            dfs(last, root);
            for(int i = 0; i <= MAXB; i++) tmp1[last][i] = 0, tmp0[last][i] = 1;
            for(auto y: V[last])
                Combine(last, y);
        }

        for(int i = 0; i <= MAXB; i++) tmp1[root][i] = 0, tmp0[root][i] = 1;
        for(auto y: V[root])
            Combine(root, y);
        for(int i = 0; i <= MAXB; i++){
            answer += (1LL << i) * tmp1[root][i];
            answer %= MOD;
        }

        for(int i = 0; i <= MAXB; i++) tmp1[root][i] = 0, tmp0[root][i] = 0;
        for(int i = 0; i <= MAXB; i++)
            if((v[root] & (1 << i)) == 0) tmp0[root][i]++;
            else tmp1[root][i]++;
        for(auto y: V[root])
            Combine(root, y);
        for(auto y: G[root]) if(v[y] >= v[root]){
            for(int i = 0; i <= MAXB; i++)
                tmp0[y][i]--;
            for(int i = 0; i <= MAXB; i++)
                if((v[root] & (1 << i)) != 0){
                    long long aux = tmp0[y][i];
                    tmp0[y][i] = tmp1[y][i];
                    tmp1[y][i] = aux;
                }
            for(int i = 0; i <= MAXB; i++){
                tmp0[root][i] -= tmp0[y][i];
                tmp1[root][i] -= tmp1[y][i];
            }
        }
        for(int i = 0; i <= MAXB; i++)
            if((v[root] & (1 << i)) == 0) tmp0[root][i]--;
            else tmp1[root][i]--;
        for(int i = 0; i <= MAXB; i++){
            answer += (1LL << i) * tmp1[root][i];
            answer %= MOD;
        }
        bad[root] = 1;
    }
    if(answer < 0) answer += MOD;
    fprintf(fo,"%lld", answer);

    fclose(fi);
    fclose(fo);
    return 0;
}
