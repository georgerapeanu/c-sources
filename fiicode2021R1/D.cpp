#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

class FenwickTree{
    int n;
    vector<long long> aib;
public:

    FenwickTree(int n){
        this->n = n;
        aib = vector<long long>(n + 1);
    }

    void update(int pos,int val){
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] += val;
        }
    }

    long long query(int pos){
        long long answer = 0;

        for(;pos;pos -= (-pos) & pos){
            answer += aib[pos];
        }

        return answer;
    }
};

int n,q;
vector<int> graph[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];
int v[NMAX + 5];
int last_id;

void dfs(int nod,int tata){
    l[nod] = ++last_id;

    for(int i = 0;i < (int)graph[nod].size();i++){
        if(graph[nod][i] == tata){
            for(int j = i;j < (int)graph[nod].size() - 1;j++){
                graph[nod][j] = graph[nod][j + 1];
            }
            graph[nod].pop_back();
            break;
        }
    }

    for(auto it:graph[nod]){
        dfs(it,nod);
    }

    r[nod] = last_id;
}

int main(){

    scanf("%d %d",&n,&q);

    FenwickTree aib(n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i < n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    for(int i = 1;i <= n;i++){
        aib.update(l[i],v[i]);
        aib.update(l[i] + 1,-v[i]);
    }

    while(q--){
        int t;
        scanf("%d",&t);

        if(t == 1){
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);

            if(l[x] <= l[y] && l[y] <= r[x]){
                int st = -1;
                int dr = (int)graph[x].size();

                while(dr - st > 1){
                    int mid = (st + dr) / 2;

                    if(l[graph[x][mid]] <= l[y]){
                        st = mid;
                    }else{
                        dr = mid;
                    }
                }

                aib.update(l[graph[x][st]],z);
                aib.update(r[graph[x][st]] + 1,-z);
            }else{
                aib.update(1,z);
                aib.update(l[x],-z);
                aib.update(r[x] + 1,z);
            }
        }else{
            int x;
            scanf("%d",&x);
            printf("%lld\n",aib.query(l[x]));
        }
    }

    return 0;
}
